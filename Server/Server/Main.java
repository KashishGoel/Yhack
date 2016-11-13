package Server;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Thread thread = new Thread(new Server());
		thread.start();
		
		Scanner scan = new Scanner(System.in);
		while (true)
		{
			if (scan.next().equals("exit"))
			{
				System.exit(0);
			}
		}

	}

}
