package Server;

import java.util.ArrayList;

import Games.Engine;
import Games.Pong;
import Objects.Player;

public class Lobby {

	final int maxPlayers = 2;
	ArrayList<Client>clients;
	Engine engine;
	char gameType;
	
	public Lobby(char gameType)
	{
		clients = new ArrayList<Client>();
		this.gameType = gameType;
	}
	
	public boolean isFull()
	{
		return (clients.size()>= maxPlayers);
	}
	
	public void checkStart()
	{
		System.out.println("Checking start");
		if (isFull())
		{
			switch(gameType)
			{
			case Engine.PONG:
				clients.get(0).createPlayer(0);
				clients.get(1).createPlayer(1);
				engine = new Pong(clients.get(0).player, clients.get(1).player);
				Thread thread = new Thread(engine);
				thread.start();
				System.out.println("Pong game started");
				break;
			case Engine.TRON:
				break;
			case Engine.GRAVITY:
				break;
			}
		}
	}
}
