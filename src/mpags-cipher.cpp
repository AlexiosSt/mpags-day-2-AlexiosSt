#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool processCommandLine(const vector<string>& args,
    bool& helpRequested, bool& versionRequested,
    string& inputFileName, string& outputFileName){
    
     // Status flag to indicate whether or not the parsing was successful
    bool processStatus{true};

    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    size_t nargs=args.size();
    for (size_t i{1}; i < nargs; ++i) {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;
        } else if (args[i] == "-v" || args[i] == "--version") {
            versionRequested = true;
        } else if (args[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nargs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                processStatus=false;
                break;
            } else {
                // Got filename, so assign value and advance past it
                inputFileName = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nargs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                processStatus=false;
                break;
            } else {
                // Got filename, so assign value and advance past it
                outputFileName = args[i + 1];
                ++i;
            }
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << args[i]
                      << "'\n";
            processStatus=false;
            break;
        }
    }
    return processStatus;
}
//===end of cmd line parsing function===

std::string transformChar(const char in_char){
    std::string out_char{""};

    if (std::isalpha(in_char)) {
        out_char = std::toupper(in_char);
    }
    else{
        switch (in_char) {
            case '0': out_char= "ZERO"; break;
            case '1': out_char= "ONE";  break;
            case '2': out_char= "TWO";  break;
            case '3': out_char= "THREE";break;
            case '4': out_char= "FOUR"; break;
            case '5': out_char= "FIVE"; break;
            case '6': out_char= "SIX";  break;
            case '7': out_char= "SEVEN";break;
            case '8': out_char= "EIGHT";break;
            case '9': out_char= "NINE"; break;
            default: break;
        }
    }
    return out_char;
 }
//===end of transliteration function===

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    bool status{false};

    status=processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile);
    if (status){
        cout<<"Parsing of command line arguments was completed!!\n";
    }
    else return 1;

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  -v|--version     Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n";
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "2.0.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::cerr << "[warning] input from file ('" << inputFile
                  << "') not implemented yet, using stdin\n";
    }

    cout<<"HELLO... now give me some chars!\n";
    cout<<"[INFO] Press ENTER and then Ctrl+D to terminate your input!!"<<endl;
    // loop over each character from user input
    while (std::cin >> inputChar) {
        inputText+=transformChar(inputChar);
    }

    // Print out the transliterated text

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        std::cerr << "[warning] output to file ('" << outputFile
                  << "') not implemented yet, using stdout\n";
    }

    cout<<"OK, you entered sth like:\n";
    std::cout << inputText << std::endl;
    cout<<"====DONE!====\n";

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}