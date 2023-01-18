/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Registery
*/

#include "Registery.hpp"
#include "Basic_Componants.hpp"
#include "Basic_Systems.hpp"

uwugine::Registery::Registery(void) : win(500, 500, "uwugine") { init_basics_systems(); }
uwugine::Registery::Registery(const Point2u &size, const std::string &title) : win(size.x, size.y, title) { init_basics_systems(); }

uwugine::entity_t uwugine::Registery::spawn_entity()
{
    auto &container = register_component<entity_t>();

    entity_t new_entity = container.get_first_pos();
    container.insert_at(new_entity, new_entity);
    return new_entity;
}

uwugine::entity_t uwugine::Registery::entity_from_index(std ::size_t idx) { return get_components<entity_t>()[idx]; }

void uwugine::Registery::kill_entity(entity_t const &e) { to_destroy.push_back(e); }

void uwugine::Registery::init_basics_systems(void)
{
    register_component<entity_t>();
    register_component<Component::controllable>();
    register_component<Component::gravity>();
    register_component<Component::hitbox>();
    register_component<Component::position>();
    register_component<Component::sound>();
    register_component<Component::sound_vector>();
    register_component<Component::sprite>();
    register_component<Component::animation>();
    register_component<Component::sprite_vector>();
    register_component<Component::text>();
    register_component<Component::text_vector>();
    register_component<Component::velocity>();
    register_component<Component::multiplayer_id>();
    add_system(Systems::move);
    add_system(Systems::gravity);
    add_system(Systems::update_velocity);
    add_system(Systems::update_pos);
    add_system(Systems::update_hitbox_pos);
    add_system(Systems::update_hitbox_colide);
    add_system(Systems::update_sprite);
    add_system(Systems::anim_sprite);
    add_system(Systems::update_text);
    add_system(Systems::update_controlable);
    add_system(Systems::draw_sprite);
    add_system(Systems::draw_text);
    add_system(Systems::check_multiplayer);
}
