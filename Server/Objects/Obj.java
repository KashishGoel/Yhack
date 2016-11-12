package Objects;

public abstract class Obj {

	public static final char PLAYER_ONE = 'P';
	public static final char PLAYER_TWO = 'p';
	
	public static final char BALL = 'B';
	public static final char SNAKE = 'S';
	
	public double x;
	public double y;
	public double hSpeed;
	public double vSpeed;
	public int width;
	public int height;
	public char type;
	
	public boolean exists;
	
	public Obj(int x, int y, int width, int height, char type, double hSpeed, double vSpeed)
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
	
	/**
	 * Check for a collision between an object and a hitbox
	 * 
	 * @param other
	 * @return whether or not the two objects are colliding
	 */
	public boolean collidesWith(double x1, double y1, double x2, double y2)
	{
		if (exists && x <= x2 && (x + width) >= x1 && y <= y2
				&& (y + height) >= y1)
		{
			return true;
		}
		return false;
	}
}
