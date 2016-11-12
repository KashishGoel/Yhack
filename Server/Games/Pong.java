package Games;

import Objects.Ball;
import Objects.Player;

public class Pong extends Engine{

	public Pong(Player playerOne, Player playerTwo ) {
		super(Engine.PONG, playerOne, playerTwo);
		objects.add(new Ball(3,3, 1, 1, 1, 1));
		objects.add(playerOne);
		objects.add(playerTwo);
	}
	
	@Override
	public void update()
	{
		super.update();
		
	}

	@Override
	public void run() {
		while (true)
		{
			update();
			try {
				Thread.sleep(15);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
	}

}
