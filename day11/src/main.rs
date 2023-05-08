use std::{fs::File, io::Read};
use std::convert::TryFrom;

fn main() -> std::io::Result<()> {
    let file_name = "./src/example.txt";
    let mut file = File::open(file_name)?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    contents = contents.split('\n').collect();
    
    let mut contents_iter = contents.chars();
    let mut matrix: [[u8; 10] ;10] = [[1; 10]; 10];
    for row in matrix.iter_mut() {
        for col in row.iter_mut() {
            let c = contents_iter.next().unwrap();
            *col = u8::try_from(c.to_digit(10).unwrap()).unwrap();
        }
    }

    let mut flashes: u64 = 0;
    for row in matrix.iter() {
        for col in row.iter() {
            // print!("[{i}][{j}] = {col} ");
            print!("{col}");
        }
        println!();
    }

    // step 1
    println!("\nstep 1");
    for _ in 0..2 {
        for i in 0..matrix.len() {
            for j in 0..(matrix[0].len()) {
                // println!("{}{}", i, j);
                let element = matrix[i][j];
                if element == 9 {
                    matrix[i][j] = 0;
                    transfer_energy(&mut matrix, i, j);
                    flashes += 1;
                } else {
                    matrix[i][j] = element + 1;
                }
            }
            // println!();
        }
    }

    println!("\nflashes: {flashes}");
    Ok(())
}

fn transfer_energy(mut matrix: &[[u8; 10] ;10], i: usize, j: usize) {
    // let dirs[u8; 2] = [0, 1, ];
    let dirs: [[i8; 2]; 8] = [
        [-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [-1, -1], [0, -1], [1, -1]
    ];
    matrix[i][j] = 8;
}
