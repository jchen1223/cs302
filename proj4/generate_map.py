import random

def generate_map(N):
    # List of tiles to choose from
    tiles = ['f', 'g', 'G', 'h', 'm', 'r']
    
    # Generate a random NxN map
    game_map = []
    for _ in range(N):
        row = [random.choice(tiles) for _ in range(N)]
        game_map.append(row)
    
    return game_map

def write_to_file(N, game_map, filename):
    # Fixed counts for each tile
    tile_counts = {
        'f': 3,
        'g': 1,
        'G': 2,
        'h': 4,
        'm': 7,
        'r': 5
    }
    
    with open(filename, 'w') as file:
         # Write the number of tiles (always 6)
        file.write("6\n")

        # Write each tile with its fixed count
        for tile, count in tile_counts.items():
            file.write(f"{tile} {count}\n")

        # Write the dimensions of the board
        file.write(f"{N} {N}\n")  # Format "N N"
        
        # Write the board
        for row in game_map:
            file.write(' '.join(row) + '\n')

        # Write the coordinates
        file.write("0 0\n")  # Starting coordinates
        file.write(f"{N-1} {N-1}\n")  # Ending coordinates

def main():
    # Ask for user input
    N = int(input("Enter the size of the map (N): "))
    
    # Generate the map
    random_map = generate_map(N)
    
    # Write to a text file
    filename = f"random_map_{N}.txt"
    write_to_file(N, random_map, filename)
    
    print(f"Map written to {filename}")

if __name__ == "__main__":
    main()
