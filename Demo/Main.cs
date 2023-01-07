using Engine;

public class Test : Script
{
    Camera cam;

    //start?
    public Test(Entity entity) : base(entity)
    {
        cam = new Camera(entity);
        entity.addComponent(cam);
    }

    public override void Update()
    {
        transform.Translate(0, 0, 0.1f);
    }

}