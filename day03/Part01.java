import java.io.*;
import java.util.*;
import java.util.stream.*;

public class Part01 { 
    public static void main(String args[]) {
        final int BIT_LEN;
        final int INITIAL_MASK;
        String filepath = null;
        if (args.length <= 0) {
            System.err.println("Input file is not provided");
            System.err.println("Using 'sample.txt'");
            filepath = "sample.txt";
            BIT_LEN = 5;
            INITIAL_MASK = 16;
        }
        else {
            BIT_LEN = 12;
            INITIAL_MASK = 512 * 4;
            filepath = args[0];
        }

        String[] lines = null;
        try (var file = new BufferedReader(new FileReader(filepath))) {
            lines = file
                .lines()
                .collect(Collectors.toList())
                .toArray(new String[0]);
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
            System.exit(1);
        }
        catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
        int[] gamma = new int[BIT_LEN];
        int bits = 0;
        for (String line : lines) {
            try {
                bits = Integer.parseInt(line, 2);
            }
            catch (NumberFormatException e) {
                System.err.println("Corrupted input in file: '" + filepath + "'");
                bits = 0;
            }
            // System.out.println(bits);
            for (int bit_field = INITIAL_MASK, idx = 0;
                    bit_field != 0;
                    bit_field = bit_field >> 1, idx++)
            {
                if (idx <= -1)
                {
                    System.err.println("error: negative index");
                    System.exit(1);
                }
                /* printf("idx: %d | bf: %d | num: %d ", idx, bit_field, bin_uint); */
                if ((bits & bit_field) == bit_field)
                {
                    gamma[idx]++;
                    /* printf("gamma: g[%d]: %d\n", idx, gamma[idx]); */
                }
                else
                {
                    gamma[idx]--;
                    /* printf("epsilon: g[%d]: %d\n", idx, gamma[idx]); */
                }

                if (idx >= BIT_LEN - 1)
                    idx = -1;
                /* gamma */
            }
        }

        String gamma_str = new String();
        String epsilon_str = new String();
        for (int i = 0; i < BIT_LEN; i++) 
        {
            // System.out.println(gamma[i]);
            if (gamma[i] > 0)
            {
                gamma_str += '1';
                epsilon_str += '0';
            }
            else
            {
                gamma_str += '0';
                epsilon_str += '1';
            }
        }
        System.out.println(gamma_str);
        System.out.println(epsilon_str);
        int gamma_val = 0;
        int epsilon_val = 0;
        try {
            gamma_val = Integer.parseInt(gamma_str, 2);
            epsilon_val = Integer.parseInt(epsilon_str, 2);
        }
        catch (NumberFormatException e) {
            System.err.println("Cannot parse the string to int");
            gamma_val = 0;
            epsilon_val = 0;
        }
        System.out.println(gamma_val);
        System.out.println(epsilon_val);
        System.out.println(gamma_val * epsilon_val);
    }
}
