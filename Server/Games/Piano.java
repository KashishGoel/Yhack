package Games;

import Objects.Ball;
import Objects.Obj;
import Objects.Player;

public class Piano extends Engine {
	
	
	
	public Piano(Player playerOne, Player playerTwo) {
		super(Engine.PONG, playerOne, playerTwo);
	}

	@Override
	public void update() {
		super.update();

	}
	
	public void broadcast(String message)
	{
		playerOne.client.sendMessage(message);
		playerTwo.client.sendMessage(message);
	}

	@Override
	public void run() {
		while (true) {
			if (end)
			{
				break;
			}
			update();
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

	}

}
