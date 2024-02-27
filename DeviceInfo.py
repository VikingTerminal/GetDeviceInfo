import os
import platform
import geocoder

def print_colored_text(text, color):
    
  print(f"\033[{color}m{text}\033[0m", end='')

def typewriter_effect(text):
    
    for char in text:
        print(char, end='', flush=True)
        os.system('sleep 0.05')

def get_location_info():
    
    location = geocoder.ip('me')

    if location and location.latlng:
        return location.latlng
    else:
        print_colored_text("Errore: Impossibile ottenere la posizione del dispositivo.", "31")  # Rosso
        exit(1)

def gather_system_info():
    
    system_info = platform.uname()
    location_info = get_location_info()
    return system_info, location_info

def display_system_info(system_info, location_info):
   
    print_colored_text("Sistema operativo: ", "36")  # Ciano
    typewriter_effect(system_info.system)
    print()

    print_colored_text("Nome host: ", "32")  # Verde
    typewriter_effect(system_info.node)
    print()

    print_colored_text("Release del kernel: ", "33")  # Giallo
    typewriter_effect(system_info.release)
    print()

    print_colored_text("Versione del kernel: ", "36")  # Ciano
    typewriter_effect(system_info.version)
    print()

    print_colored_text("Macchina: ", "32")  # Verde
    typewriter_effect(system_info.machine)
    print()

    print_colored_text("Latitudine: ", "36")  # Ciano
    typewriter_effect(str(location_info[0]))
    print()

    print_colored_text("Longitudine: ", "33")  # Giallo
    typewriter_effect(str(location_info[1]))
    print()

def save_system_info_to_file(system_info, location_info):
    
    choice = input("Do you want to save the system information to a file? (yes/no): ")

    if choice.lower() == "yes":
        filename = input("Enter the filename: ")
        if not filename.endswith('.txt'):
            filename += '.txt'

        with open(filename, 'a') as file:
            file.write(f"Sistema operativo: {system_info.system}\n")
            file.write(f"Nome host: {system_info.node}\n")
            file.write(f"Release del kernel: {system_info.release}\n")
            file.write(f"Versione del kernel: {system_info.version}\n")
            file.write(f"Macchina: {system_info.machine}\n")
            file.write(f"Latitudine: {location_info[0]}\n")
            file.write(f"Longitudine: {location_info[1]}\n")

        print(f"Result saved to the file {filename}.")
    elif choice.lower() != "no":
        print_colored_text("Invalid response. Program termination.\n", "31")  
        exit(1)

def main():
    system_info, location_info = gather_system_info()
    display_system_info(system_info, location_info)
    save_system_info_to_file(system_info, location_info)
    print_colored_text("Grazie per aver usato questo tool. Prova altre utility. Visita https://github.com/VikingTerminal", "36")  # Ciano chiaro

if __name__ == "__main__":
    main()
