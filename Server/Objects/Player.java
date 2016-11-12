package Objects;

import Server.Client;

public class Player extends Obj {

	public Client client;
	public Player(int x, int y, int width, int height, char type, Client client) {
		super(x, y, width, height, type, 0, 0);
		this.client = client;
	}
}
