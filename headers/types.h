#ifndef TYPES_H
#define TYPES_H


#define MAX_ENTITY_COUNT 512


#define MAX_RECIPE_ITEMS 8

// font
Gfx_Font* font;
u32 font_height = 48;

// globals
float64 delta_t;
float64 current_time;
int fps = 0;
Vector2 camera_pos = {0, 0};
const char res_folder[17] = "res/abyssophobia/";

// rendering layers
const s32 layer_ui = 20;
const s32 layer_workstation_ui = 15;
const s32 layer_world = 10;


// ENUMS --------------------------------------------->

    typedef enum EntityID {
        ENTITY_nil,

        ENTITY_player,
        ENTITY_item, // EntityID for all items
        ENTITY_rock,
        ENTITY_algae,
        ENTITY_workstation,

        ENTITY_tool, // get rid of this. this is currently only used for categories inside workbench
        



        ENTITY_MAX,
    } EntityID;

    typedef enum ItemID{
        ITEM_nil,

        ITEM_rock,
        ITEM_algae,


        ITEM_MAX,
    } ItemID;

    typedef enum SpriteID{
        SPRITE_nil,

        SPRITE_player,
        SPRITE_algae1,

        // categories
        SPRITE_CATEGORY_items,
        SPRITE_CATEGORY_all,
        SPRITE_CATEGORY_tools,
        SPRITE_CATEGORY_workstations,

        SPRITE_MAX,
    } SpriteID;

    typedef enum BackgroundID{
        BACKGROUND_nil,

        BACKGROUND_hub,
        // BACKGROUND_level_1,

        BACKGROUND_MAX,
    } BackgroundID;

    typedef enum UXState{
        UX_nil,

        UX_gameplay,
        UX_workbench,
        UX_settings,

        UX_MAX,
    } UXState;

    typedef enum GameState{
        GAMESTATE_nil,

        GAMESTATE_mainmenu, // self explanatory
        GAMESTATE_hub,      // main island hub
        GAMESTATE_level,    // diving
        GAMESTATE_map,      // level selection
        // GAMESTATE_pause, // ??????????

        GAMESTATE_MAX,
    } GameState;

// 

// STRUCTS ------------------------------------------->

    typedef struct WorldFrame {
        // Entity* selected_entity;
        Matrix4 world_projection;
        Matrix4 world_view;
        bool hover_consumed;
        // Entity* player;
    } WorldFrame;


    typedef struct Sprite {
        Gfx_Image* image;
    } Sprite;


    typedef struct Background{
        Gfx_Image* image;
        bool has_custom_size;
        Vector2 custom_size;
    } Background;


    typedef struct ItemAmount {
        ItemID id;
        int amount;
    } ItemAmount;


    typedef struct ItemData{
        string name;
        int amount;
        SpriteID sprite_id;
        ItemID item_id;
        EntityID id;
        ItemAmount crafting_recipe[MAX_RECIPE_ITEMS];
        int crafting_recipe_count; // how many types of items in recipe ????? or output
        EntityID category;
        float cooking_time;
        string tooltip;
        bool valid;
    } ItemData;



    typedef struct Entity{
        string name;
        EntityID entity_id;
        Vector2 pos;
        SpriteID sprite;

        bool is_item;
        ItemID item_id;


        int health;
        bool is_destroyable;
        bool is_selectable;
        // bool enabled;
        bool is_valid;
    } Entity;


    // :WorkstationData -------------------->
    typedef struct WorkstationData { 
        // EntityArchetype to_build;
        EntityID to_build;
        SpriteID sprite_id;
        // WorkStationID workstation_id;
        bool has_inventory;
        // InventoryItemData inventory[ITEM_MAX];
        ItemData *selected_crafting_item;
        int crafting_queue;
        float64 crafting_end_time;
        Entity* en;
        // display name
        // cost
        // health
        // etc
    } WorkstationData;


    typedef struct Player{
        Entity* en;

        int health;
        float oxygen;
        float oxygen_consumption;   // ogygen consumption rate
        float oxygen_refill;        // oxygen refill rate

        bool is_running;
        int walking_speed;
        int running_speed;

        // inventory
        int inventory_items_count;
        ItemData inventory[ITEM_MAX];

        bool inventory_ui_open;
        WorkstationData* selected_workstation; // selected workstation || currently open workstation

    } Player;


    typedef struct World{
        int entity_count;
        Entity entities[MAX_ENTITY_COUNT];
        // Entity* player;
        Player* player;
        UXState ux_state;
        GameState game_state;


        Entity* open_crafting_station;
        float workbench_alpha_target;
        float workbench_alpha;
    } World;


    typedef struct Range2f {
        Vector2 min;
        Vector2 max;
    } Range2f;


// 


// globals

    World* world = 0;
    WorldFrame world_frame;
    Sprite sprites[SPRITE_MAX];
    Background backgrounds[BACKGROUND_MAX];


    // workstation UI
    EntityID workbench_tab_category = ENTITY_nil;
    ItemData* selected_recipe_workbench = NULL;
    ItemData* selected_recipe_furnace = NULL;
    Matrix4 selected_recipe_xform;
    bool is_recipe_selected = false;

    // recipes
    ItemData workbench_recipes[ITEM_MAX];
    ItemData furnace_recipes[ITEM_MAX];

// 



#endif