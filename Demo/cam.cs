using Engine;
using System;

class CameraController : Script
{
    Entity plate;




    public CameraController(Entity entity) : base(entity)
    {
        plate = new Entity();
        MeshRenderer mesh = new MeshRenderer(plate);
        plate.addComponent(mesh);
        plate.transform.setScale(0.1f);

        Input.setCursorState(3);//locked and hidden
        //ManagedWindow.SetFullscreen(true);
    }

    public override void Update()
    {
        //close on escape
        if (Input.getKey(0x1B))//VK_ESCAPE = 0x1B
        {
            //ManagedWindow.Close();
            throw new Exception("Closed");
        }

        float speed = 5 * Time.deltaTime();
        if(Input.getKey('W'))
            transform.Translate(0, 0, speed);
        if (Input.getKey('A'))
            transform.Translate(-speed, 0, 0);
        if (Input.getKey('S'))
            transform.Translate(0, 0, -speed);
        if (Input.getKey('D'))
            transform.Translate(speed, 0, 0);

        float sensitivity = 50 * Time.deltaTime();
        Vec2 mouse = Input.getMouse();
        transform.Rotate(mouse.y * sensitivity, mouse.x * sensitivity, 0);

        //limit position
        Vec3 newPos = transform.getPosition();
        newPos.y = 2;

        //collision alternative
        newPos.x = Math.Max(newPos.x, -10);
        newPos.x = Math.Min(newPos.x, 10);

        newPos.z = Math.Max(newPos.z, -10);
        newPos.z = Math.Min(newPos.z, 10);

        transform.setPosition(newPos.x, newPos.y, newPos.z);

        //limit rotation
        Vec3 newRot = transform.getRotation();

        newRot.x = Math.Max(newRot.x, -90);
        newRot.x = Math.Min(newRot.x, 90);

        transform.setRotation(newRot.x, newRot.y, newRot.z);

        //move plate
        Vec3 f = transform.foreward();
        f.x += newPos.x;
        f.y = 1.5f;
        f.z += newPos.z;
        plate.transform.setPosition(f.x, f.y, f.z);

        //check what has been clicked on
        clickedOn(new Vec2(), new Vec2());
    }

    bool clickedOn(Vec2 a, Vec2 b)
    {
        //get line from camera
        Vec2 a2 = new Vec2(transform.getPosition().x, transform.getPosition().z);
        Vec2 b2 = new Vec2(transform.foreward().x + a2.x, transform.foreward().z + a2.y);

        //find point of intersection
        float slope1 = (b.y - a.y) / (b.x - a.x);
        float slope2 = (b2.y - a2.y) / (b2.x - a2.x);

        float A1 = a.y - b.y;
        float A2 = a2.y - b2.y;

        float B1 = b.x - a.x;
        float B2 = b2.x - a2.x;

        float C1 = (a.y - (slope1 * a.x)) * -B1;
        float C2 = (a2.y - (slope2 * a2.x)) * -B2;

        Vec2 intersection = new Vec2();
        intersection.x = ((B1 * C2) - (B2 * C1)) / ((A1 * B2) - (A2 * B1));
        intersection.y = ((A2 * C1) - (A1 * C2)) / ((A1 * B2) - (A2 * B1));

        //check if intersection is on input line segment
        if(Math.Min(a.x, b.x) < intersection.x && intersection.x < Math.Max(a.x, b.x))
            if (Math.Min(a.y, b.y) < intersection.y && intersection.y < Math.Max(a.y, b.y))
                return true;
        return false;
    }
}
