package Objects;

import Server.Client;

public class Snake extends Player {
	public Snake(int x, int y, int width, int height,char type, double hSpeed, double vSpeed,Client client){
		super(x, y, width, height, type, client); 
		this.hSpeed = hSpeed;
		this.vSpeed = vSpeed;
	}
}
