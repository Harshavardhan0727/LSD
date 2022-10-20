#include <iostream>
#include <chrono>
#include "FASTA_readset.cpp"
using namespace std;
using namespace std::chrono;

int main(int argc, char **args)
{

    if (argc < 3)
    {

        cout << "Invalid number of arguments!" << endl;
        cout << "Proper usage: ./output [filename] [part {A1, A2, B, C} \n\n";
    }

    char part = args[2][0];
    int num_q = 0;

    if (argc > 3)
        num_q = atoi(args[3]);

    //14 instances of the class, and each containing sequences for different dataset
    FASTA_readset f1(args[1], 1);
    FASTA_readset f2(args[1], 2);
    FASTA_readset f3(args[1], 3);
    FASTA_readset f4(args[1], 4);
    FASTA_readset f5(args[1], 5);
    FASTA_readset f6(args[1], 6);
    FASTA_readset f7(args[1], 7);
    FASTA_readset f8(args[1], 8);
    FASTA_readset f9(args[1], 9);
    FASTA_readset f10(args[1], 10);
    FASTA_readset f11(args[1], 11);
    FASTA_readset f12(args[1], 12);
    FASTA_readset f13(args[1], 13);
    FASTA_readset f14(args[1], 14);
    if (part == 'A1')
    {
        cout << "Unique Sequence Fragments in dataset 1: " << f1.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 2: " << f2.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 3: " << f3.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 4: " << f4.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 5: " << f5.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 6: " << f6.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 6: " << f6.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 7: " << f7.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 8: " << f8.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 9: " << f9.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 10: " << f10.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 11: " << f11.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 12: " << f12.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 13: " << f13.get_unique_segments_count() << endl;
        cout << "Unique Sequence Fragments in dataset 14: " << f14.get_unique_segments_count() << endl;
    }
    if (part == 'A2')
    {

        cout << "Total Sequence Fragments in dataset 1 (with copies) : " << f1.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 2 (with copies) : " << f2.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 3 (with copies) : " << f3.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 4 (with copies) : " << f4.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 5 (with copies) : " << f5.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 6 (with copies) : " << f6.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 7 (with copies) : " << f7.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 8 (with copies) : " << f8.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 9 (with copies) : " << f9.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 10 (with copies) : " << f10.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 11 (with copies) : " << f11.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 12 (with copies) : " << f12.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 13 (with copies) : " << f13.get_total_segments_count() << endl
             << endl;
        cout << "Total Sequence Fragments in dataset 14 (with copies) : " << f14.get_total_segments_count() << endl
             << endl;
    }

    if (part == 'B')
    {

        if (num_q > f1.get_unique_segments_count() || num_q == 0)
            num_q = f1.get_unique_segments_count();

        int matches = 0;

        auto start = high_resolution_clock::now();

        for (int i = 0; i < num_q; i++)
            if (f2.linear_search(f1.get_fragment(i)) == true)
                matches++;

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "\nFor " << num_q << " Queries: \n";

        cout << "Time taken (milliseconds): " << duration.count() << endl;

        cout << "Total matching fragments: " << matches << endl;
    }

    if (part == 'C')
    {

        //sort the dataset
        f2.sort_alphabetically();

        if (num_q > f1.get_unique_segments_count() || num_q == 0)
            num_q = f1.get_unique_segments_count();

        int matches = 0;

        auto start = high_resolution_clock::now();

        for (int i = 0; i < num_q; i++)
            if (f2.binary_search(f1.get_fragment(i)) == true)
                matches++;

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "\nFor " << num_q << " Queries: \n";

        cout << "Time taken (milliseconds): " << duration.count() << endl;

        cout << "Total matching fragments: " << matches << endl;
    }
    //f1.print_arrays();
}
