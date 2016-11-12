package Server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

import Objects.Player;

public class Client {

	Socket socket;
	BufferedReader reader;
	PrintWriter writer;
	Lobby lobby;
	Player player;
	
	/**
	 * 
	 * @param socket
	 * @param input
	 * @param output
	 */
	public Client(Socket socket, BufferedReader input, PrintWriter output, Lobby lobby)
	{
		this.socket = socket;
		this.reader = input;
		this.writer = output;
		this.lobby = lobby;
		
		Thread thread = new Thread(new Writer());
		thread.start();
		thread = new Thread(new Reader());
		thread.start();
	}
	
	
	public class Writer implements Runnable
	{
		@Override
		public void run() {
			while (true)
			{
				writer.println("okay");
				writer.flush();
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
		}
	}
	
	public class Reader implements Runnable
	{
		@Override
		public void run() {
			while(true)
			{
				try {
					String message = reader.readLine();
					System.out.println("Player: " + message);
					
				} catch (IOException e) {
					break;
				}
			}
		}
	}
}
