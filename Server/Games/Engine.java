package Games;

import java.util.ArrayList;

import Objects.Obj;
import Objects.Player;
import Objects.Snake;

public abstract class Engine implements Runnable{

	public final static char PONG = 'p';
	public final static char TRON = 't';
	public final static char PIANO = 'P';
	
	public char type;
	
	public ArrayList<Obj> objects;
	
	public Player playerOne;
	public Player playerTwo;
	
	public boolean end;
	
	public Engine(char type, Player one, Player two)
	{
		this.type = type;
		this.objects = new ArrayList<Obj>();
		this.playerOne = one;
		this.playerTwo = two;
		this.end = false;
	}
	
	public Engine(char type, Snake one, Snake two)
	{
		this.type = type;
		this.objects = new ArrayList<Obj>();
		this.playerOne = one;
		this.playerTwo = two;
	}

	public void update()
	{
	}
	
}
