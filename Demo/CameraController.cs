using Engine;
using System;
using System.ComponentModel;

class CameraController : Script
{
    //Start is called after construction
    public override void Start()
    {
        Input.setCursorState(3);//locked and hidden
        //Application.SetFullscreen(true);
    }

    //Update is called every frame
    public override void Update()
    {
        //close on escape
        if (Input.getKey(0x1B))//VK_ESCAPE = 0x1B
        {
            Application.Close();
            return;
        }

        //move
        float speed = 5 * Time.deltaTime();
        if(Input.getKey('W'))
            transform.Translate(0, 0, speed);
        if (Input.getKey('A'))
            transform.Translate(-speed, 0, 0);
        if (Input.getKey('S'))
            transform.Translate(0, 0, -speed);
        if (Input.getKey('D'))
            transform.Translate(speed, 0, 0);

        //look
        float sensitivity = 50 * Time.deltaTime();
        Vec2 mouse = Input.getMouse();
        transform.Rotate(mouse.y * sensitivity, mouse.x * sensitivity, 0);

        //confine player to plane
        Vec3 newPos = transform.getPosition();
        newPos.y = 2;

        newPos.x = Math.Max(newPos.x, -10);
        newPos.x = Math.Min(newPos.x, 10);

        newPos.z = Math.Max(newPos.z, -10);
        newPos.z = Math.Min(newPos.z, 10);

        transform.setPosition(newPos.x, newPos.y, newPos.z);

        //limit rotation of camera
        Vec3 newRot = transform.getRotation();

        newRot.x = Math.Max(newRot.x, -90);
        newRot.x = Math.Min(newRot.x, 90);

        transform.setRotation(newRot.x, newRot.y, newRot.z);
    }
}
