package Games;

import Objects.Snake;
import Objects.Obj;

public class Tron extends Engine{
	public Snake snake1; 
	public Snake snake2; 
	
	public Tron(Snake snake1, Snake snake2){
		super(Engine.TRON, snake1, snake2);
		
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
			
			object.update();
		}
		snake1.client.updateClient(this);
		snake2.client.updateClient(this);
	}
	public void broadcast(String message)
	{
		snake1.client.sendMessage(message);
		snake2.client.sendMessage(message);
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
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
