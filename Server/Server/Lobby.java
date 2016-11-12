package Server;

import java.util.ArrayList;

import Games.Engine;

public class Lobby {

	final int maxPlayers = 2;
	ArrayList<Client>clients;
	Engine engine;
	char gameType;
	
	public Lobby(Engine game)
	{
		clients = new ArrayList<Client>();
		this.engine = game;
		this.gameType = game.type;
	}
	
	public boolean isFull()
	{
		return (clients.size()>= maxPlayers);
	}
}
