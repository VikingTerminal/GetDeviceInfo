#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <fstream>
#include <sstream>

void printColoredText(const std::string& text, const std::string& color) {
    std::cout << "\033[" << color << "m" << text << "\033[0m";
}

void typeWriterEffect(const std::string& text) {
    for (char c : text) {
        std::cout << c << std::flush;
        usleep(50000);
    }
}

void printMemoryInfo() {
    struct sysinfo mem_info;
    if (sysinfo(&mem_info) != 0) {
        perror("Errore nel recupero delle informazioni sulla memoria");
        exit(EXIT_FAILURE);
    }

    printColoredText("Memoria disponibile: ", "36");
    typeWriterEffect(std::to_string(mem_info.totalram / (1024 * 1024)) + " MB");
    std::cout << std::endl;

    printColoredText("Memoria libera: ", "32");
    typeWriterEffect(std::to_string(mem_info.freeram / (1024 * 1024)) + " MB");
    std::cout << std::endl;
}

void printFileSystemInfo() {
    struct statvfs fs_info;
    if (statvfs("/tmp", &fs_info) != 0) {
        perror("Errore nel recupero delle informazioni sul filesystem");
        exit(EXIT_FAILURE);
    }

    printColoredText("Spazio disponibile su /tmp: ", "36");
    typeWriterEffect(std::to_string(fs_info.f_bavail * fs_info.f_frsize / (1024 * 1024)) + " MB");
    std::cout << std::endl;

    printColoredText("Dimensione totale del filesystem /tmp: ", "32");
    typeWriterEffect(std::to_string(fs_info.f_blocks * fs_info.f_frsize / (1024 * 1024)) + " MB");
    std::cout << std::endl;

    printColoredText("Dimensione blocco filesystem /tmp: ", "33");
    typeWriterEffect(std::to_string(fs_info.f_frsize) + " bytes");
    std::cout << std::endl;
}

void printCpuInfo() {
    std::ifstream cpuInfoFile("/proc/cpuinfo");
    if (!cpuInfoFile.is_open()) {
        perror("Errore nell'apertura di /proc/cpuinfo");
        exit(EXIT_FAILURE);
    }

    std::string line;
    int coreCount = 0;

    while (std::getline(cpuInfoFile, line)) {
        if (line.find("processor") != std::string::npos) {
            coreCount++;
        }
    }

    printColoredText("Numero di core CPU: ", "36");
    typeWriterEffect(std::to_string(coreCount));
    std::cout << std::endl;
}

void printNetworkInfo() {
    std::ifstream netDevFile("/proc/net/dev");
    if (!netDevFile.is_open()) {
        perror("Errore nell'apertura di /proc/net/dev");
        exit(EXIT_FAILURE);
    }

    std::string line;
    int interfaceCount = 0;

    while (std::getline(netDevFile, line)) {
        if (line.find(":") != std::string::npos) {
            interfaceCount++;
        }
    }

    printColoredText("Numero di interfacce di rete: ", "32");
    typeWriterEffect(std::to_string(interfaceCount));
    std::cout << std::endl;
}

int main() {
    struct utsname system_info;

    if (uname(&system_info) != 0) {
        perror("Errore nel recupero delle informazioni di sistema");
        exit(EXIT_FAILURE);
    }

    printColoredText("\033[1;96mBenvenuto in questo tool da t.me/VikingTerminal\033[0m", "96");
    typeWriterEffect(" \nottieni informazioni device!\n ");
    std::cout << std::endl;

    printColoredText("Sistema operativo: ", "36");
    typeWriterEffect(system_info.sysname);
    std::cout << std::endl;

    printColoredText("Nome host: ", "32");
    typeWriterEffect(system_info.nodename);
    std::cout << std::endl;

    printColoredText("Release del kernel: ", "33");
    typeWriterEffect(system_info.release);
    std::cout << std::endl;

    printColoredText("Versione del kernel: ", "36");
    typeWriterEffect(system_info.version);
    std::cout << std::endl;

    printColoredText("Macchina: ", "32");
    typeWriterEffect(system_info.machine);
    std::cout << std::endl;

    printMemoryInfo();
    printFileSystemInfo();
    printCpuInfo();
    printNetworkInfo();

    return 0;
}
