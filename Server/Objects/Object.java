package Objects;

public abstract class Object {

	public static final char PLAYER_ONE = 'P';
	public static final char PLAYER_TWO = 'p';
	
	public static final char BALL = 'B';
	
	public double x;
	public double y;
	public double hSpeed;
	public double vSpeed;
	public int width;
	public int height;
	public char type;
	
	public boolean exists;
	
	public Object(int x, int y, int width, int height, char type, double hSpeed, double vSpeed)
	{
		this.type = type;
		this.exists =true;
		this.x=x;
		this.y=y;
		this.width=width;
		this.height=height;
		this.hSpeed = hSpeed;
		this.vSpeed = vSpeed;
	}
	
	public void update()
	{
		this.x+=hSpeed;
		this.y+=vSpeed;
	}
}
