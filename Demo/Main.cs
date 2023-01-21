using Engine;
using System;
class Runtime{

    static int Main()
    {
        //*** Create Application ***//
        Application application = new Application("Name of window", 1280, 720, true);

        //*** Create & Load Section ***//

        //create scene
        Scene scene = new Scene();

        //create player Entity
        Entity player = scene.CreateEntity();
        player.transform.setPosition(0, 2, 0);

        //add script to player
        CameraController controller = new CameraController();
        player.addComponent(controller);

        //add camera component to player
        Camera comp = new Camera(player);
        comp.setFOV(60);

        //create floor Entity
        Entity floor = scene.CreateEntity();

        //add mesh to floor
        MeshRenderer mesh = new MeshRenderer(floor);
        mesh.ImportMeshObj("assets/plane.obj");

        //create sun Entity
        Entity sun = scene.CreateEntity();
        sun.transform.setRotation(45, 45, 0);

        //add directional light to sun
        DirectionalLight light = new DirectionalLight(sun);

        //*** Run Application ***//
        Script[] scripts = { controller };
        return application.Run(scripts);
    }
}
