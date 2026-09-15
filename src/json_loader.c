#include "json_loader.h"

static char* read_file(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) {
        printf("Impossible d'ouvrir: %s\n", path);
        return NULL;
    }
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }
    
    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);
    return buffer;
}

static void parse_stats(cJSON* stats_json, Statistics* stats) {
    cJSON* field;
    
    field = cJSON_GetObjectItem(stats_json, "max_hp");
    if (cJSON_IsNumber(field)) stats->max_hp = field->valueint;
    
    field = cJSON_GetObjectItem(stats_json, "atk");
    if (cJSON_IsNumber(field)) stats->atk = field->valueint;
    
    field = cJSON_GetObjectItem(stats_json, "def");
    if (cJSON_IsNumber(field)) stats->def = field->valueint;
    
    field = cJSON_GetObjectItem(stats_json, "speed");
    if (cJSON_IsNumber(field)) stats->speed = field->valueint;
    
    field = cJSON_GetObjectItem(stats_json, "atk_speed");
    if (cJSON_IsNumber(field)) stats->atk_speed = field->valueint;
}

static Entity* parse_entity(cJSON* entity_json) {
    cJSON* name_field = cJSON_GetObjectItem(entity_json, "name");
    cJSON* stats_field = cJSON_GetObjectItem(entity_json, "stats");
    
    if (!cJSON_IsString(name_field)) {
        printf("Entite sans nom valide\n");
        return NULL;
    }
    
    if (!cJSON_IsObject(stats_field)) {
        printf("Entite '%s' sans stats\n", name_field->valuestring);
        return NULL;
    }

    Statistics* stats = InitBasicStats();
    parse_stats(stats_field, stats);
    Entity* entity = initEntity(name_field->valuestring, stats);
    return entity;
}

EntityDatabase* loadEntitiesFromJson(const char* filepath) {
    char* content = read_file(filepath);
    if (!content) return NULL;
    
    cJSON* root = cJSON_Parse(content);
    free(content);
    
    if (!root) {
        const char* error = cJSON_GetErrorPtr();
        printf("Erreur JSON: %s\n", error ? error : "inconnue");
        return NULL;
    }
    
    EntityDatabase* db = (EntityDatabase*)malloc(sizeof(EntityDatabase));
    db->player = NULL;
    db->entities = NULL;
    db->entity_count = 0;
    
    cJSON* player_json = cJSON_GetObjectItem(root, "player");
    if (cJSON_IsObject(player_json)) {
        db->player = parse_entity(player_json);
    }
    
    cJSON* entities_json = cJSON_GetObjectItem(root, "entities");
    if (cJSON_IsArray(entities_json)) {
        int count = cJSON_GetArraySize(entities_json);
        db->entities = (Entity**)malloc(sizeof(Entity*) * count);
        
        int i = 0;
        cJSON* entity_json = NULL;
        cJSON_ArrayForEach(entity_json, entities_json) {
            Entity* e = parse_entity(entity_json);
            if (e) {
                db->entities[i] = e;
                i++;
            }
        }
        db->entity_count = i;
    }
    
    cJSON_Delete(root);
    
    printf("Charge : 1 joueur + %d entites\n", db->entity_count);
    return db;
}

void destroyEntityDatabase(EntityDatabase* db) {
    if (!db) return;
    
    if (db->player) destroyEntity(db->player);
    
    if (db->entities) {
        for (int i = 0; i < db->entity_count; i++) {
            if (db->entities[i]) destroyEntity(db->entities[i]);
        }
        free(db->entities);
    }
    
    free(db);
}