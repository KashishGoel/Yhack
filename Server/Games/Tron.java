package Games;

import Objects.Snake;
import Objects.Obj;
import Objects.Player;

public class Tron extends Engine{
	public Snake snake1; 
	public Snake snake2; 
	
	public Tron(Player playerOne, Player playerTwo){
		super(Engine.TRON, playerOne, playerTwo);
		
		snake1 = new Snake(10,3,10,3,0.1,0.1);
		snake2 = new Snake(10,3,10,3,0.1,0.1);
		objects.add(snake1);
		objects.add(snake2);
		objects.add(playerOne);
		objects.add(playerTwo);
		
	}
	
	@Override
	public void update() {}
	public void broadcast(String message)
	{
		playerOne.client.sendMessage(message);
		playerTwo.client.sendMessage(message);
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		while (true) {
			update();
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	
}
