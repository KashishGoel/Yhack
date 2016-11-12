package Objects;

public abstract class Obj {

	public static final char PLAYER_ONE = 'P';
	public static final char PLAYER_TWO = 'p';
	
	public static final char BALL = 'B';
	public static final char SNAKE_ONE = 'S';
	public static final char SNAKE_TWO = 's';
	
	public double x;
	public double y;
	public double hSpeed;
	public double vSpeed;
	public int width;
	public int height;
	public char type;
	public static double[] x1Coordinates = {0,1,2,3};
	public static double[] y1Coordinates = {0,0,0,0};
	public static double[] x2Coordinates = {15,14,13,12};
	public static double[] y2Coordinates = {5,5,5,5};
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
//		this.x+=hSpeed;
//		this.y+=vSpeed;
		for(int i = 0; i < 3; i++){
			x1Coordinates[i] = x1Coordinates[i+1];
			y1Coordinates[i] = y1Coordinates[i+1];
			x2Coordinates[i] = x2Coordinates[i+1];
			y2Coordinates[i] = y2Coordinates[i+1];

		}
		
		x1Coordinates[3] = x1Coordinates[3] + 1;
		y1Coordinates[3] = y1Coordinates[3];
		x2Coordinates[3] = x2Coordinates[3];
		y2Coordinates[3] = y2Coordinates[3] + 1;
		
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
