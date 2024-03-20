require 'open-uri'
require 'geocoder'

def print_colored_text(text, color)
  puts "\033[#{color}m#{text}\033[0m"
end

def typewriter_effect(text)
  text.each_char do |char|
    print char
    sleep 0.05
  end
end

def get_location_info
  location = Geocoder.search('me').first

  if location && location.coordinates
    return location.coordinates
  else
    print_colored_text("Errore: Impossibile ottenere la posizione del dispositivo.", "31")
    exit(1)
  end
end

def gather_system_info
  system_info = RbConfig::CONFIG
  location_info = get_location_info
  return system_info, location_info
end

def display_system_info(system_info, location_info)
  print_colored_text("Sistema operativo: ", "36")
  typewriter_effect(system_info['host_os'])
  puts

  print_colored_text("Nome host: ", "32")
  typewriter_effect(`hostname`.strip)
  puts

  print_colored_text("Release del kernel: ", "33")
  typewriter_effect(`uname -r`.strip)
  puts

  print_colored_text("Versione del kernel: ", "36")
  typewriter_effect(`uname -v`.strip)
  puts

  print_colored_text("Macchina: ", "32")
  typewriter_effect(system_info['host_cpu'])
  puts

  print_colored_text("Latitudine: ", "36")
  typewriter_effect(location_info[0].to_s)
  puts

  print_colored_text("Longitudine: ", "33")
  typewriter_effect(location_info[1].to_s)
  puts
end

def save_system_info_to_file(system_info, location_info)
  puts "Vuoi salvare le informazioni di sistema su un file? (sì/no): "
  choice = gets.chomp.downcase

  if choice == "sì" || choice == "si"
    print "Inserisci il nome del file: "
    filename = gets.chomp
    filename += '.txt' unless filename.end_with?('.txt')

    File.open(filename, 'a') do |file|
      file.puts "Sistema operativo: #{system_info['host_os']}"
      file.puts "Nome host: #{`hostname`.strip}"
      file.puts "Release del kernel: #{`uname -r`.strip}"
      file.puts "Versione del kernel: #{`uname -v`.strip}"
      file.puts "Macchina: #{system_info['host_cpu']}"
      file.puts "Latitudine: #{location_info[0]}"
      file.puts "Longitudine: #{location_info[1]}"
    end

    puts "Risultato salvato nel file #{filename}."
  elsif choice != "no"
    print_colored_text("Risposta non valida. Termine del programma.\n", "31")
    exit(1)
  end
end

def main
  system_info, location_info = gather_system_info
  display_system_info(system_info, location_info)
  save_system_info_to_file(system_info, location_info)
  print_colored_text("Grazie per aver usato questo tool. Prova altre utility. Visita https://github.com/VikingTerminal", "36")
end

if __FILE__ == $PROGRAM_NAME
  main
end
