# Yhack Corsair Winner

#Inspiration
Our inspiration was to look at the world of gaming in a different way, little did we know that we would literally be looking at it in a different way. We inspired to build a real time engine that would allow for the quick development of keyboard games.

# What it does
Allows users to use custom built libraries to quickly set up player objects, instances and keyboard program environments on a local server that can support multiple threads and multiple game instances. We built multiple games using our engine to demonstrate its scalability.

# How we built it
The server was built using Java and the front end was built using Visual C++. The server includes customizable objects and classes that can easily be modified to create a wide array of products. All of the server creation/game lobbies/multi threading/real time is handled by the engine. The front end engine created in C++ creates a 16x6 grid on the Corsair keyboards, allocates values to keys, registers keys and pre defined functions for easy LED manipulation. The front end engine provides the base template for easy manipulation and fast development of programs on the keyboard.

# Challenges we ran into
Our unique selling proposition was the ability to use our engine to create real time programs/games. Creating this involved many challenges primarily surrounding latency and packet loss. Due to the fact that our engine was expected to allow every keyboard playing in a lobby to reflect the state of every other place, and update the LED UI without delay, this required a low latency which became a problem using 1and1 servers located in the UK leading to the response time with different keyboards increasing up to a few seconds.

## Watch it in action: https://www.youtube.com/watch?v=i_8VQVfulDs
