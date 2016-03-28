#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>
#include <glm/basics.hpp>
#include <SFML/Graphics.hpp>

class Entity
{
    using Vector3 = glm::vec3;

    public:
        Entity ()
        { }

        Entity ( const Vector3& rotation, const Vector3& position, const Vector3& scale )
        :   m_rotation  ( rotation )
        ,   m_position  ( position )
        ,   m_scale     ( scale )
        { }

        //Rotation getters and setters
        inline void
        setRotation     ( const Vector3& rotation )     { m_rotation = rotation; }

        inline void
        changeRotation  ( const Vector3& rotation )     { m_rotation += rotation; }

        inline const Vector3&
        getRotation     () const                        { return m_rotation; }


        //Position getters and setters
        inline void
        setPosition     ( const Vector3& position )     { m_position = position; }

        inline void
        changePosition  ( const Vector3& position )     { m_position += position; }

        inline const Vector3&
        getPosition     () const                        { return m_position; }


        //Scale getters and setters
        inline void
        setScale        ( const Vector3& scale )        { m_scale = scale; }

        inline void
        changeScale     ( const Vector3& scale )        { m_scale += scale; }

        inline const Vector3&
        getScale        () const                        { return m_scale; }

        //Velocity getters and setters
        inline void
        setVelocity     ( const Vector3& velocity )     { m_velocity = velocity; }

        inline void
        changeVelocity  ( const Vector3& velocity )     { m_velocity += velocity; }

        inline const Vector3&
        getVelocity     () const                        { return m_velocity; }

    protected:
        inline Vector3&
        getRotationRef  ()                              { return m_rotation; }

    private:
        Vector3 m_rotation;
        Vector3 m_position;
        Vector3 m_scale     { 1, 1, 1 };

        Vector3 m_velocity;
};

#endif // ENTITY_H
