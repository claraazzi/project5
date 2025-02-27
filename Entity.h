#ifndef ENTITY_H
#define ENTITY_H

#include "Map.h"
#include "glm/glm.hpp"
#include "ShaderProgram.h"

enum EntityType { PLATFORM, PLAYER, ENEMY };
enum AIType {
   WALKER,
   GUARD,
   SPINNER,
   VERTICAL_MOVER,
   HORIZONTAL_MOVER,
    JUMPER
};

enum AIState { WALKING, IDLE, ATTACKING };
enum AnimationDirection { LEFT, RIGHT, UP, DOWN };

class Entity
{
private:
   // Entity state
   bool m_is_active = true;

   // Transformations
   glm::vec3 m_position;
   glm::vec3 m_movement;
   glm::vec3 m_velocity;
   glm::vec3 m_acceleration;
   glm::vec3 m_scale = glm::vec3(1.0f);
   glm::mat4 m_model_matrix = glm::mat4(1.0f);

   // Animation
   int m_walking[4][4];
   int* m_animation_indices = nullptr;
   int m_animation_frames = 0;
   int m_animation_index = 0;
   int m_animation_cols = 0;
   int m_animation_rows = 0;
   float m_animation_time = 0.0f;
    int m_killed_enemies = 0;

   // AI behavior
   EntityType m_entity_type;
   AIType m_ai_type;
   AIState m_ai_state;

   // Physical properties
   float m_speed = 0.0f;
   float m_jumping_power = 0.0f;
   float m_width = 1.0f;
   float m_height = 1.0f;
   float m_rotation = 0.0f;

   // Collision flags
   bool m_collided_top = false;
   bool m_collided_bottom = false;
   bool m_collided_left = false;
   bool m_collided_right = false;

   // Texture
   GLuint m_texture_id = 0;

   // Jumping state
   bool m_is_jumping = false;

public:
   // Constants
   static constexpr int SECONDS_PER_FRAME = 4;

   // Constructors and Destructor
   Entity();
   Entity(GLuint texture_id, float speed, glm::vec3 acceleration, float jump_power, int walking[4][4],
          float animation_time, int animation_frames, int animation_index, int animation_cols,
          int animation_rows, float width, float height, EntityType EntityType);
   Entity(GLuint texture_id, float speed, float width, float height, EntityType EntityType);
   Entity(GLuint texture_id, float speed, float width, float height, EntityType EntityType, AIType AIType, AIState AIState);
   ~Entity();

   // AI methods
   bool bool_val = false;
   void ai_activate(Entity* player);
   void ai_walk();
   void ai_guard(Entity* player);
   void ai_spin();
   void ai_move_vertical();
   void ai_move_horizontal();
    void ai_jump();

   // Collision handling
   bool const check_collision(Entity* other) const;
   void const check_collision_y(Entity* collidable_entities, int collidable_entity_count);
   void const check_collision_x(Entity* collidable_entities, int collidable_entity_count);
   void const check_collision_y(Map* map);
   void const check_collision_x(Map* map);

   // Update and Render
   void update(float delta_time, Entity* player, Entity* collidable_entities, int collidable_entity_count, Map* map);
   void render(ShaderProgram* program);
   void draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index);

   // Movement and animation
   void normalise_movement() { m_movement = glm::normalize(m_movement); }
   void move_left() { m_movement.x = -1.0f; face_left(); }
   void move_right() { m_movement.x = 1.0f; face_right(); }
   void move_up() { m_movement.y = 1.0f; face_up(); }
   void move_down() { m_movement.y = -1.0f; face_down(); }
   void const jump() { m_is_jumping = true; }

   // Facing directions
   void face_left() { m_animation_indices = m_walking[LEFT]; }
   void face_right() { m_animation_indices = m_walking[RIGHT]; }
   void face_up() { m_animation_indices = m_walking[UP]; }
   void face_down() { m_animation_indices = m_walking[DOWN]; }

   // Interaction
   void const attacking(Entity* other);

   // Getters
   EntityType const get_entity_type() const { return m_entity_type; }
   AIType const get_ai_type() const { return m_ai_type; }
   AIState const get_ai_state() const { return m_ai_state; }
   glm::vec3 const get_position() const { return m_position; }
   glm::vec3 const get_velocity() const { return m_velocity; }
   glm::vec3 const get_acceleration() const { return m_acceleration; }
   glm::vec3 const get_movement() const { return m_movement; }
   glm::vec3 const get_scale() const { return m_scale; }
   GLuint const get_texture_id() const { return m_texture_id; }
   float const get_speed() const { return m_speed; }
   bool const get_collided_top() const { return m_collided_top; }
   bool const get_collided_bottom() const { return m_collided_bottom; }
   bool const get_collided_left() const { return m_collided_left; }
   bool const get_collided_right() const { return m_collided_right; }
   bool is_active() const { return m_is_active; }

   // Setters
   void activate() { m_is_active = true; }
   void deactivate() { m_is_active = false; }
   void const set_entity_type(EntityType new_entity_type) { m_entity_type = new_entity_type; }
   void const set_ai_type(AIType new_ai_type) { m_ai_type = new_ai_type; }
   void const set_ai_state(AIState new_state) { m_ai_state = new_state; }
   void const set_position(glm::vec3 new_position) { m_position = new_position; }
   void const set_velocity(glm::vec3 new_velocity) { m_velocity = new_velocity; }
   void const set_acceleration(glm::vec3 new_acceleration) { m_acceleration = new_acceleration; }
   void const set_movement(glm::vec3 new_movement) { m_movement = new_movement; }
   void const set_scale(glm::vec3 new_scale) { m_scale = new_scale; }
   void const set_texture_id(GLuint new_texture_id) { m_texture_id = new_texture_id; }
   void const set_speed(float new_speed) { m_speed = new_speed; }
   void const set_animation_cols(int new_cols) { m_animation_cols = new_cols; }
   void const set_animation_rows(int new_rows) { m_animation_rows = new_rows; }
   void const set_animation_frames(int new_frames) { m_animation_frames = new_frames; }
   void const set_animation_index(int new_index) { m_animation_index = new_index; }
   void const set_animation_time(float new_time) { m_animation_time = new_time; }
   void const set_jumping_power(float new_jumping_power) { m_jumping_power = new_jumping_power; }
   void const set_width(float new_width) { m_width = new_width; }
   void const set_height(float new_height) { m_height = new_height; }

   // Walking animation setter
   void set_walking(int walking[4][4])
   {
       for (int i = 0; i < 4; ++i)
       {
           for (int j = 0; j < 4; ++j)
           {
               m_walking[i][j] = walking[i][j];
           }
       }
   }
};

#endif // ENTITY_H




