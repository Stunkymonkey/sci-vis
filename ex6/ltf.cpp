#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

// Lena image source: http://graphics.stanford.edu/~jowens/223b/examples.html

/**
 * Reads gray-value images in PGM format.
 *
 * @param filename Full path to the file.
 * @param numcols Width of the image.
 * @param numrows Height of the image.
 * @param maxval Maximum gray value a pixel can have.
 *
 * @return The image pixels.
 */
std::vector<unsigned char> readPGM(std::string const& filename, int& numcols, int& numrows, int& maxval) {
    // https://stackoverflow.com/questions/8126815/how-to-read-in-data-from-a-pgm-file-in-c
    std::ifstream infile(filename, std::ios::binary);

    std::string buffer;

    std::getline(infile, buffer);
    if (buffer != "P5") {
        std::cerr << "Not a valid PGM file" << std::endl;
    }
    else {
        std::cout << "PGM Version: " << buffer << std::endl;
    }

    std::getline(infile, buffer);
    std::cout << "Comment: " << buffer << std::endl;

    infile >> numcols >> numrows;

    std::cout << "Image size: " << numcols << "x" << numrows << std::endl;

    infile >> maxval;

    int entrysize = 1;
    if (maxval >= 256) entrysize = 2;
    std::vector<unsigned char> ret(numcols * numrows * entrysize);

    infile.read(reinterpret_cast<char*>(ret.data()), numcols * numrows * entrysize);

    infile.close();

    return ret;
}


/**
 * Writes a gray-value image in PGM format.
 *
 * @param filename The full path to the file.
 * @param image The pixels of the image.
 * @param numcols The width of the image.
 * @param numrows The height of the image.
 * @param maxval Maximum gray-value of a pixel.
 */
void writePGM(std::string const& filename, std::vector<unsigned char> const& image, int numcols, int numrows, int maxval) {
    std::ofstream outfile(filename, std::ios::binary);

    outfile << "P5\n";
    outfile << "#\n";
    outfile << numcols << " " << numrows << "\n";
    outfile << maxval << "\n";

    outfile.write(reinterpret_cast<char const*>(image.data()), image.size());

    outfile.close();
}


/**
 * Writes a color image in PPM format.
 *
 * @param filename The full path to the file.
 * @param image The pixels of the image.
 * @param numcols The width of the image.
 * @param numrows The height of the image.
 * @param maxval Maximum color-value of a pixel.
 */
void writePPM(std::string const& filename, std::vector<unsigned char> const& image, int numcols, int numrows, int maxval) {
    std::ofstream outfile(filename, std::ios::binary);

    outfile << "P6\n";
    outfile << "#\n";
    outfile << numcols << " " << numrows << "\n";
    outfile << maxval << "\n";

    outfile.write(reinterpret_cast<char const*>(image.data()), image.size());

    outfile.close();
}


/**
 * Creates a piecewise linear transfer function lookup table from the given color samples.
 *
 * @param tf_size Length of the lookup table.
 * @param samples Vector of color samples that are the basis for the tf.
 *   Each sample has an index that positions the sample in the lookup table and an array that represents RGB color.
 *
 * @return The transfer function lookup table.
 */
std::vector<unsigned char> createTF(unsigned int tf_size, std::vector<std::pair<unsigned int, std::array<unsigned char, 3>>> samples) {
    // TODO Implement an algorithm that creates the piecewise linear transfer function in the form of a lookup table
    std::vector<unsigned char> tf(tf_size * 3);

    // TODO Implement this
    for (int i = 0; i < tf_size; i++)
    {
	    // std::cout << "#" << i << std::endl;
	    if (i >= samples.at(0).first && i < samples.at(1).first) {
			int range = samples.at(1).first - samples.at(0).first;
			float percent_second = i / ((float) range - 1);
			float percent_first = 1 - percent_second;

			tf.at(i * 3 + 0) = (samples.at(0).second.at(0) * percent_first) + (samples.at(1).second.at(0) * percent_second);
			tf.at(i * 3 + 1) = (samples.at(0).second.at(1) * percent_first) + (samples.at(1).second.at(1) * percent_second);
			tf.at(i * 3 + 2) = (samples.at(0).second.at(2) * percent_first) + (samples.at(1).second.at(2) * percent_second);
	    } else if (i >= samples.at(1).first && i < samples.at(2).first) {
			int range = samples.at(2).first - samples.at(1).first;
			float percent_second = (i - samples.at(1).first) / ((float) range - 1);
			float percent_first = 1 - percent_second;

			tf.at(i * 3 + 0) = (samples.at(1).second.at(0) * percent_first) + (samples.at(2).second.at(0) * percent_second);
			tf.at(i * 3 + 1) = (samples.at(1).second.at(1) * percent_first) + (samples.at(2).second.at(1) * percent_second);
			tf.at(i * 3 + 2) = (samples.at(1).second.at(2) * percent_first) + (samples.at(2).second.at(2) * percent_second);
	    }
    }

    return tf;
}


/**
 * Applies the given transfer function on the gray-value image.
 *
 * @param image The gray-value image.
 * @param tf The transfer function lookup table.
 *
 * @return The RGB color image.
 */
std::vector<unsigned char> applyTF(std::vector<unsigned char> const& image, std::vector<unsigned char> const& tf) {
    // TODO Apply the transfer function on the image by selecting the correct samples from the lookup table and interpolate between them for each pixel
    std::vector<unsigned char> output(image.size() * 3);

    // TODO Implement this
    for (int i = 0; i < image.size(); ++i)
    {
    	int value = image.at(i);
    	int index = value / 2;
    	bool is_uneven = value % 2;

    	if (is_uneven) {
	    	unsigned char r1 = tf.at(index * 3 + 0);
	    	unsigned char r2 = tf.at(index * 3 + 0);
	    	unsigned char g1 = tf.at(index * 3 + 1);
	    	unsigned char g2 = tf.at(index * 3 + 1);
	    	unsigned char b1 = tf.at(index * 3 + 2);
	    	unsigned char b2 = tf.at(index * 3 + 2);
	    	output.at((i * 3) + 0) = (r1 + r2) / 2;
	    	output.at((i * 3) + 1) = (g1 + g2) / 2;
	    	output.at((i * 3) + 2) = (b1 + b2) / 2;
    	} else {
	    	output.at((i * 3) + 0) = tf.at(index * 3 + 0);
	    	output.at((i * 3) + 1) = tf.at(index * 3 + 1);
	    	output.at((i * 3) + 2) = tf.at(index * 3 + 2);
    	}
    }

    return output;
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: ltf <input filename> <output filename>" << std::endl;
        return -1;
    }

    int numrows = 0, numcols = 0, maxval = 0;

    std::cout << "Reading input" << std::endl;
    std::string const infilename(argv[1]);
    auto image = readPGM(infilename, numcols, numrows, maxval);

    if (maxval > 255) {
        std::cerr << "No support for shorts as pixel entries" << std::endl;
        return -1;
    }

    std::cout << "Creating TF" << std::endl;
    auto const tf = createTF(128, { { 0, { 0, 255, 0 } }, {64, {255, 0, 0}}, { 128, { 0, 0, 255 } } });

    std::cout << "Applying TF" << std::endl;
    auto const out_image = applyTF(image, tf);

    std::cout << "Writing output" << std::endl;
    std::string const outfilename(argv[2]);
    writePPM(outfilename, out_image, numcols, numrows, maxval);

    return 0;
}
