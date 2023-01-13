using Engine;
using System;
class Runtime{

    static int Main()
    {
        try
        {
            //create window
            ManagedWindow window = new ManagedWindow("Name of window", 1920, 1080);

            //load
            Entity cam = new Entity();
            CameraController controller = new CameraController(cam);
            cam.transform.setPosition(0, 2, 0);
            Camera comp = new Camera(cam);

            cam.addComponent(comp);
            comp.setFOV(60);

            Entity floor = new Entity();
            MeshRenderer mesh = new MeshRenderer(floor);
            mesh.getMesh().ImportObj("assets/world.obj");
            floor.addComponent(mesh);

            Entity light = new Entity();
            DirectionalLight dir = new DirectionalLight(light);
            light.transform.setRotation(45, 45, 0);
            light.addComponent(dir);

            Script[] scripts = { controller };
            //run program
            return window.Run(scripts);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }

        return -1;
    }
}
