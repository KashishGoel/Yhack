package Games;

import Objects.Ball;
import Objects.Obj;
import Objects.Player;

public class Pong extends Engine {

	public int pOnePoints = 0;
	public int pTwoPoints = 0;
	public Ball ball;
	public static double speed = 0.3;
	
	public Pong(Player playerOne, Player playerTwo) {
		super(Engine.PONG, playerOne, playerTwo);
		ball =new Ball(7, 3, 1, 2, speed, speed);
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
							object.y = 6 + object.vSpeed;
							object.vSpeed *= -1;
						}
					} else if (object.vSpeed < 0) {
						if (object.y + object.vSpeed <= 0) {
							object.y = -1 + object.vSpeed;
							object.vSpeed *= -1;
						}
					}

					if (object.hSpeed > 0) {
						if (object.collidesWith(playerTwo.x - object.hSpeed, playerTwo.y - object.vSpeed,
								playerTwo.x + playerTwo.width - object.hSpeed,
								playerTwo.y + playerTwo.height - object.vSpeed)) {
							object.x=playerTwo.x-1+object.hSpeed;
							
							switch((int)(Math.random()*3))
							{
							case 0:
								object.hSpeed = -speed;
								object.vSpeed = speed * Math.abs(object.vSpeed)/object.vSpeed;
								break;
							case 1:
								object.hSpeed = -speed*2/3.0;
								object.vSpeed = 3/2.0*speed * Math.abs(object.vSpeed)/object.vSpeed;
								break;
							case 2:
								object.hSpeed = -speed*5/4.0;
								object.vSpeed = 5/4.0*speed * Math.abs(object.vSpeed)/object.vSpeed;
								break;
							}
						}
						else if (object.x+object.hSpeed>=16)
						{
							pOnePoints ++;
							broadcast("p");
							object.x = 7;
							object.y=3;
							object.hSpeed = speed;
							object.vSpeed = speed;
							playerOne.client.writer.printf("%.2f %.2f %.2f %.2f\n", ball.x, ball.y, playerOne.y, playerTwo.y);
							playerOne.client.writer.flush();
							
							playerTwo.client.writer.printf("%.2f %.2f %.2f %.2f\n", ball.x, ball.y, playerOne.y, playerTwo.y);
							playerTwo.client.writer.flush();
							try {
								Thread.sleep(2000);
							} catch (InterruptedException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
							object.x = 7;
							object.y=3;
							object.hSpeed = speed;
							object.vSpeed = speed;
						}
					}
					else if (object.hSpeed < 0)
					{
						if (object.collidesWith(playerOne.x - object.hSpeed, playerOne.y - object.vSpeed,
								playerOne.x + playerOne.width - object.hSpeed,
								playerOne.y + playerOne.height - object.vSpeed)) {
							object.x=playerOne.x + playerOne.width +object.hSpeed;
							
							switch((int)(Math.random()*3))
							{
							case 0:
								object.hSpeed = speed;
								object.vSpeed = speed * Math.abs(object.vSpeed)/object.vSpeed;
								break;
							case 1:
								object.hSpeed = speed*2/3.0;
								object.vSpeed = 3/2.0*speed * Math.abs(object.vSpeed)/object.vSpeed;
								break;
							case 2:
								object.hSpeed = speed*5/4.0;
								object.vSpeed = 4/5.0*speed * Math.abs(object.vSpeed)/object.vSpeed;
								break;
							}
						}
						else if (object.x+object.hSpeed<=-1)
						{
							pTwoPoints ++;
							broadcast("P");
							object.x = 7;
							object.y=3;
							object.hSpeed = speed;
							object.vSpeed = speed;
							playerOne.client.writer.printf("%.2f %.2f %.2f %.2f\n", ball.x, ball.y, playerOne.y, playerTwo.y);
							playerOne.client.writer.flush();
							
							playerTwo.client.writer.printf("%.2f %.2f %.2f %.2f\n", ball.x, ball.y, playerOne.y, playerTwo.y);
							playerTwo.client.writer.flush();
							try {
								Thread.sleep(2000);
							} catch (InterruptedException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
							object.x = 7;
							object.y=3;
							object.hSpeed = speed;
							object.vSpeed = speed;
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
