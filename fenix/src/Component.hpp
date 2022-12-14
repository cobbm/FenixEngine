#pragma once

namespace Fenix
{
    class Object3D;

    class Component
    {
    public:
        // Component() = delete;

        Component(Object3D &owner) : ownerObject(owner){};

        virtual ~Component() = default;

        bool hasStarted() { return componentStarted; }
        // Behaviour(int test) {
        //     cout<<"Hello!!!"<<endl;
        // };
        void init()
        {
            if (!componentStarted)
            {
                start();
                componentStarted = true;
            }
        };
        virtual void start(){};
        // virtual void update() {cout <<"Base Update"<<endl;};
        virtual void update(){};

    protected:
        Object3D &ownerObject;

        bool componentStarted = false;
    };
} // namespace Fenix
