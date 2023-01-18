using Engine;
using System;
class Runtime{

    static int Main()
    {
        try
        {
            //create window
            ManagedWindow window = new ManagedWindow("Name of window", 1280, 720);

            //create and load
            Entity cam = new Entity();
            CameraController controller = new CameraController(cam);
            cam.transform.setPosition(0, 2, 0);
            Camera comp = new Camera(cam);

            Camera.getMain();

            cam.addComponent(comp);
            comp.setFOV(60);

            Entity floor = new Entity();
            MeshRenderer mesh = new MeshRenderer(floor);
            mesh.ImportMeshObj("assets/plane.obj");

            Entity light = new Entity();
            DirectionalLight dir = new DirectionalLight(light);
            light.transform.setRotation(45, 45, 0);

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
