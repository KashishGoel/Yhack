package Games;

import Objects.Ball;
import Objects.Obj;
import Objects.Player;

public class Pong extends Engine {

	public int pOnePoints = 0;
	public int pTwoPoints = 0;
	public Ball ball;
	
	public Pong(Player playerOne, Player playerTwo) {
		super(Engine.PONG, playerOne, playerTwo);
		ball =new Ball(3, 3, 1, 1, 0.1, 0.1);
		objects.add(ball);
		objects.add(playerOne);
		objects.add(playerTwo);
		System.out.println("Create PONG");
	}

	@Override
	public void update() {
		super.update();
		for (Obj object : objects) {
			try{
				switch (object.type) {
				case Obj.BALL:
					if (object.vSpeed > 0) {
						if (object.y + object.vSpeed >= 5) {
							object.y = 5;
							object.vSpeed *= -1;
						}
					} else if (object.vSpeed < 0) {
						if (object.y + object.vSpeed <= 0) {
							object.y = 0;
							object.vSpeed *= -1;
						}
					}

					if (object.hSpeed > 0) {
						if (object.collidesWith(playerTwo.x - object.hSpeed, playerTwo.y - object.vSpeed,
								playerTwo.x + playerTwo.width - object.hSpeed,
								playerTwo.y + playerTwo.height - object.vSpeed)) {
							object.x=playerTwo.x-1+object.hSpeed;
							object.hSpeed*=-1;
						}
						else if (object.x+object.hSpeed>=16)
						{
							pOnePoints ++;
							broadcast("p");
							object.x = 3;
							object.y=3;
							object.hSpeed = -0.1;
							object.vSpeed = -0.1;
							try {
								Thread.sleep(5000);
							} catch (InterruptedException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}
					}
					else if (object.hSpeed < 0)
					{
						if (object.collidesWith(playerOne.x - object.hSpeed, playerOne.y - object.vSpeed,
								playerOne.x + playerOne.width - object.hSpeed,
								playerOne.y + playerOne.height - object.vSpeed)) {
							object.x=playerOne.x + playerOne.width +object.hSpeed;
							object.hSpeed*=-1;
						}
						else if (object.x+object.hSpeed<=-1)
						{
							pTwoPoints ++;
							broadcast("P");
							object.x = 3;
							object.y=3;
							object.hSpeed = 0.1;
							object.vSpeed = 0.1;
							try {
								Thread.sleep(5000);
							} catch (InterruptedException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}
					}
					break;
				case Obj.PLAYER_ONE:
				case Obj.PLAYER_TWO:
					if (object.vSpeed > 0 && object.y + object.height + object.vSpeed >= 6)
					{
						object.vSpeed = 0;
						object.y = 6- object.height;
					}
					else if (object.vSpeed < 0 && object.y + object.vSpeed<= 0)
					{
						object.vSpeed = 0;
						object.y = 0;
					}
					break;
				}
			}
			catch(NullPointerException e)
			{
				e.printStackTrace();
				if (playerOne == null)
				{
					System.out.println("1");
				}
				if (playerTwo == null)
				{
					System.out.println("2");
				}
				if (ball == null)
				{
					System.out.println("3");
				}
			}
			
			object.update();
		}
		
		playerOne.client.updateClient(this);
		playerTwo.client.updateClient(this);

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
				Thread.sleep(30);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

	}

}
