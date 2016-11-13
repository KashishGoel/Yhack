package Server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;

import Games.Engine;
import Games.Pong;
import Games.Tron;
import Objects.Obj;
import Objects.Player;
import Objects.Snake;

public class Client {

	Socket socket;
	BufferedReader reader;
	public PrintWriter writer;
	Lobby lobby;
	Player player;
	int playerNo;
	StringBuilder longMessage;
	ArrayList<String> toSend;
	boolean disconnect;
	private double x;
	private double y1;
	private double x1;

	/**
	 * 
	 * @param socket
	 * @param input
	 * @param output
	 */
	public Client(Socket socket, BufferedReader input, PrintWriter output, Lobby lobby) {
		toSend = new ArrayList<String>();
		longMessage = new StringBuilder();
		this.socket = socket;
		this.reader = input;
		this.writer = output;
		this.lobby = lobby;
		this.disconnect = false;

		Thread thread = new Thread(new Reader());
		thread.start();
	}

	public void updateClient(Engine engine) {
		if (engine.type == Engine.PONG) {
			Pong pong = (Pong) engine;
			writer.printf("%.2f %.2f %.2f %.2f\n", pong.ball.x, pong.ball.y, pong.playerOne.y, pong.playerTwo.y);
			writer.flush();

//			System.out.printf("%.2f %.2f %.2f %.2f\n", pong.ball.x, pong.ball.y,
//					pong.playerOne.y, pong.playerTwo.y);
		}
		else if (engine.type == Engine.TRON) {
			x1 = ((Tron)lobby.engine).snake1.x;
			y1 = ((Tron)lobby.engine).snake1.y;
			//System.out.printf("x1 y1:%.2f %.2f\n",x1,y1);
			writer.printf("%.2f %.2f ", x1,y1);
			for (int i = 2; i >= 0; i--) {
			//	System.out.printf("Orig:%.2f", Obj.x1Coordinates[i]);
				writer.printf("%d %d ", Math.round(1.0*Obj.x1Coordinates[i]-x1), Math.round(1.0*Obj.y1Coordinates[i]-y1));
			//	System.out.printf("x y: %d %d\n",Math.round(1.0*Obj.x1Coordinates[i]-x1),Math.round(1.0*Obj.y1Coordinates[i]-y1));
			}
			double x2 = ((Tron)lobby.engine).snake2.x;
			double y2 = ((Tron)lobby.engine).snake2.y;
			writer.printf("%.2f %.2f ", x2,y2);
			System.out.printf("x2 y2:%.2f %.2f\n",x2,y2);
			for (int i = 2; i >= 0; i--) {
				writer.printf("%d %d", Math.round(1.0*Obj.x2Coordinates[i]-x2), Math.round(Obj.y2Coordinates[i]-y2));
				if (i > 0) {
					writer.print(" ");
				}
			}

			writer.print("\n");

			writer.flush();

			//System.out.printf("%.2f %.2f %.2f %.2f\n", tron.snake1.x, tron.snake1.y,
			//		tron.playerOne.y, tron.playerTwo.y);

			// System.out.printf("%.2f %.2f %.2f %.2f\n", tron.snake1.x,
			// tron.snake1.y,
			// tron.playerOne.y, tron.playerTwo.y);

		}

	}

	public class Reader implements Runnable {
		@Override
		public void run() {
			while (true) {
				try {
					String message = reader.readLine();
					
					if (disconnect)
					{
						break;
					}
					
					message = message.substring(message.indexOf("MSG")+3);
					for (int no = 0; no<message.length(); no++)
					{
						if (Character.isLetter(message.charAt(no))|| Character.isDigit(message.charAt(no)))
						{
							message =message.substring(no);
							break;
						}
					}
					
					if (message.equals("EXIT"))
					{
						System.out.println("Player exited");
						break;
					}
					
					System.out.println("Player: " + message);

					if (lobby.gameType == Engine.PONG) {
						switch (message) {
						case "UpPressed":
							player.vSpeed = -0.3;
							if (player.y>= 0)
							{
								player.y -= 0.8;
								if (player.y <= 0)
								{
									player.vSpeed = 0;
									player.y = 0;
								}
							}
							break;
						case "UpReleased":
							player.vSpeed = 0;
							break;
						case "DownPressed":
							player.vSpeed = 0.3;
							if (player.y + player.height <= 6)
							{
								player.y+=0.8;
								if ( player.y + player.height >= 6)
								{
									player.vSpeed = 0;
									player.y = 6- player.height;
								}
							}
							break;
						case "DownReleased":
							player.vSpeed = 0;
							break;
						}
					} else if (lobby.gameType == Engine.TRON) {
						switch (message) {
						case "reset":
							System.out.println("RESET THIS");
							for(int i=0;i<=3;i++){
								Obj.x1Coordinates[i] = Obj.originalX1[i];
								((Tron)lobby.engine).snake1.x = 3;
								((Tron)lobby.engine).snake1.y = 0;
								((Tron)lobby.engine).snake2.x = 7;
								((Tron)lobby.engine).snake2.y = 5;
								((Tron)lobby.engine).snake1.hSpeed = 1; 
								((Tron)lobby.engine).snake1.vSpeed = 0;
								((Tron)lobby.engine).snake2.hSpeed = -1;
								((Tron)lobby.engine).snake2.vSpeed = 0;
								Obj.x2Coordinates[i] = Obj.originalX2[i];
								Obj.y1Coordinates[i] = 0;
								Obj.y2Coordinates[i] = 5; 
							}

							
						case "Up":
							if (player.vSpeed <=0)
							{
							player.vSpeed = -1;
							player.hSpeed = 0;
							}
							break;
						case "Down":
							if(player.vSpeed>=0){
							player.vSpeed = 1;
							player.hSpeed = 0;}
							break;
						case "Left":
							if(player.hSpeed<=0){
							player.hSpeed = -1;
							player.vSpeed = 0;}
							break;
						case "Right":
							if(player.hSpeed>=0){
							player.hSpeed = 1;
							player.vSpeed =0;}
							break;
						}
					} else if (lobby.gameType == Engine.PIANO)
					{
						if (player.type==Obj.PLAYER_ONE)
						{
						lobby.engine.playerTwo.client.sendMessage(message);
						}
						else
						{
							lobby.engine.playerOne.client.sendMessage(message);
						}
					}
					
					

				} catch (IOException e) {
					break;
				}
			}
			if (!disconnect)
			{
				System.out.println("Closing lobby");
				Server.removeLobby(lobby);
			}
			System.out.println("Player has disconnected");
			disconnect = true;
			writer.close();
			try {
				reader.close();
			} catch (IOException e1) {

				e1.printStackTrace();
			}
			try {
				socket.close();
			} catch (IOException e1) {

				e1.printStackTrace();
			}
		}
	}

	public void sendMessage(String message) {
		writer.println(message);
		writer.flush();
	}
	
	public void broadcast(String message)
	{
		lobby.engine.playerOne.client.sendMessage(message);
		lobby.engine.playerTwo.client.sendMessage(message);
	}

	public void queueMessage(String message) {
		longMessage.append(message + " ");
	}

	public void flush() {
		String string = longMessage.toString().trim();
		writer.println(string);
		writer.flush();
	}

	public void createPlayer(int playerNo) {
		this.playerNo = playerNo;
		if (playerNo == 0) {
			this.player = new Player(0, 0, 1, 1, Obj.PLAYER_ONE, this);
		} else {
			this.player = new Player(15, 0, 1, 1, Obj.PLAYER_TWO, this);
		}
	}

	public void createSnake(int playerNo) {
		this.playerNo = playerNo;
		if (playerNo == 0) {
			this.player = new Snake(0, 0, 1, 2, Obj.SNAKE_ONE, 0.1, 0, this);
		} else {
			this.player = new Snake(15, 0, 1, 2, Obj.SNAKE_TWO, -0.1, 1, this);
		}
	}
}
