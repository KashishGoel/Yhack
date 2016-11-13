package Games;

import Objects.Snake;
import Objects.Obj;

public class Tron extends Engine{
	public Snake snake1; 
	public Snake snake2; 
	
	public Tron(Snake snake1, Snake snake2){
		super(Engine.TRON, snake1, snake2);
		snake1.x = 3.0;
		snake1.y = 0.0;
		snake2.x = 7.0;
		snake2.y = 5.0;
		
		snake1.hSpeed = 1;
		snake1.vSpeed = 0;
		snake2.hSpeed = -1;
		snake2.vSpeed = 0; 
		
		this.snake1 = snake1;
		this.snake2 = snake2;
		objects.add(snake1);
		objects.add(snake2);
		
	}
	
	@Override
	public void update() {
		super.update();
		for(Obj object:objects){
			try{
				switch(object.type){
				case Obj.SNAKE_ONE:
//					if (object.vSpeed > 0) {
//						if (object.y + object.vSpeed >= 5) {
//							object.y = 5;
//							object.vSpeed *= -1;
//						}
//					} else if (object.vSpeed < 0) {
//						if (object.y + object.vSpeed <= 0) {
//							object.y = 0;
//							object.vSpeed *= -1;
//						}
//					}
				}
			}catch(NullPointerException e)
			{
				e.printStackTrace();
				if (snake1 == null)
				{
					System.out.println("1");
				}
				if (snake2 == null)
				{
					System.out.println("2");
				}
				if (snake1 == null)
				{
					System.out.println("3");
				}
				if(snake2 == null){
					System.out.println("4");
				}
			}
			
		}
		snake1.client.updateClient(this);
		snake2.client.updateClient(this);
		for(int i = 0; i < 3; i++){
			System.out.printf("%.2f\n", Obj.y2Coordinates[i]);
			Obj.x1Coordinates[i] = Obj.x1Coordinates[i+1];
			
			Obj.y1Coordinates[i] = Obj.y1Coordinates[i+1];
			Obj.x2Coordinates[i] = Obj.x2Coordinates[i+1];
			Obj.y2Coordinates[i] = Obj.y2Coordinates[i+1];
			System.out.printf("%.2f\n", Obj.y2Coordinates[i]);

		}
		
		snake1.x = snake1.x + snake1.hSpeed;
		snake1.y = snake1.y + snake1.vSpeed; 
		snake2.x = snake2.x + snake2.hSpeed;
		snake2.y = snake2.y + snake2.vSpeed;
		Obj.x1Coordinates[3] = snake1.x; 
		Obj.y1Coordinates[3] = snake1.y; 
		Obj.x2Coordinates[3] = snake2.x; 
		Obj.y2Coordinates[3] = snake2.y; 
		//System.out.printf("speed:%.2f\n", Obj.x1Coordinates[3]);
		if(snake1.x>10) snake1.x -=10; 
		if (snake1.y>5) snake1.y -= 5; 
		if (snake2.x>10) snake2.x -= 10; 
		if (snake2.y>5) snake2.y -= 5; 
		
		if(snake1.x<0) snake1.x +=10; 
		if (snake1.y<0) snake1.y += 5; 
		if (snake2.x<0) snake2.x += 10; 
		if (snake2.y<0) snake2.y += 5; 
		//System.out.printf("speed:%.2f\n", Obj.x1Coordinates[3]);
		

	}
	public void broadcast(String message)
	{
		snake1.client.sendMessage(message);
		snake2.client.sendMessage(message);
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
				Thread.sleep(500);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	
}
