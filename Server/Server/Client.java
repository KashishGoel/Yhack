package Server;

import java.io.BufferedReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Client {

	Socket socket;
	BufferedReader reader;
	PrintWriter writer;
	Lobby lobby;
	
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
	}
}
