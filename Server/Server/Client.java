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
	PrintWriter writer;
	Lobby lobby;
	Player player;
	int playerNo;
	StringBuilder longMessage;
	ArrayList<String> toSend;

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

		Thread thread = new Thread(new Writer());
		thread.start();
		thread = new Thread(new Reader());
		thread.start();
	}

	public void updateClient(Engine engine) {
		if (engine.type == Engine.PONG) {
			Pong pong = (Pong) engine;
			writer.printf("%.2f %.2f %.2f %.2f\n", pong.ball.x, pong.ball.y,
					pong.playerOne.y, pong.playerTwo.y);
			writer.flush();
//			System.out.printf("%.2f %.2f %.2f %.2f\n", pong.ball.x, pong.ball.y,
//					pong.playerOne.y, pong.playerTwo.y);
		}
		else if (engine.type == Engine.TRON) {
			System.out.printf("Tron\n");

			for (int i = 3; i >= 0; i--)
			{
				writer.printf("%.2f %.2f ", Obj.x1Coordinates[i], Obj.y1Coordinates[i]);
			}
			for (int i = 3; i >= 0; i--)
			{
				writer.printf("%.2f %.2f", Obj.x2Coordinates[i], Obj.y2Coordinates[i]);
				if (i > 0)
				{
					writer.print(" ");
				}
			}
			
			writer.print("\n");

			writer.flush();
			for(int i = 0; i < 4; i++){
			
//				System.out.print(Obj.x1Coordinates[i]);
//				System.out.printf("y1:%g\n", Obj.y1Coordinates[i]);
//				System.out.print(Obj.x1Coordinates[3]);
//				System.out.printf("y2:%g\n", Obj.y2Coordinates[i]);
			}
			//System.out.printf("%.2f %.2f %.2f %.2f\n", tron.snake1.x, tron.snake1.y,
			//		tron.playerOne.y, tron.playerTwo.y);
		}
		
	}

	public class Writer implements Runnable {
		@Override
		public void run() {
			while (true) {
//				for (String string : toSend) {
//					writer.println(string);
//				}
//				writer.flush();
//				toSend.clear();
				try {
					Thread.sleep(1);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}

		}
	}

	public class Reader implements Runnable {
		@Override
		public void run() {
			while (true) {
				try {
					String message = reader.readLine();
					System.out.println("Player: " + message);

				} catch (IOException e) {
					break;
				}
			}
		}
	}

	public void sendMessage(String message) {
		writer.println(message);
		writer.flush();
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
			this.player = new Player(0, 0, 1, 2, Obj.PLAYER_ONE, this);
		} else {
			this.player = new Player(15, 0, 1, 2, Obj.PLAYER_TWO, this);
		}
	}
	
	public void createSnake(int playerNo) {
		this.playerNo = playerNo;
		if (playerNo == 0) {
			this.player = new Snake(0, 0, 1, 2, Obj.SNAKE_ONE,0.1,0, this);
		} else {
			this.player = new Snake(15, 0, 1, 2, Obj.SNAKE_TWO,-0.1,1, this);
		}
	}
}
