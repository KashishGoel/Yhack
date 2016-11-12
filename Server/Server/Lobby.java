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
		if (isFull())
		{
			switch(gameType)
			{
			case Engine.PONG:
				
				//engine = new Pong(clients.get(0), clients.get(1));
				break;
			case Engine.TRON:
				break;
			case Engine.GRAVITY:
				break;
			}
		}
	}
}
