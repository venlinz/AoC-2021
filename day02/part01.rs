use std::fs;

fn main() {
    let filename = "input.txt";
    let contents = fs::read_to_string(filename)
         .expect("Can't open file for reading");
    let split_line = contents.split("\n");

    let mut total_forward_distance = 0;
    let mut total_depth = 0;
    for line in split_line {
        let direction = line.split_whitespace().next().unwrap_or("");
        let throttle = line.split_whitespace().last().unwrap_or("");
        let num: i32 = throttle.parse::<i32>().unwrap_or(0); 
        if direction.chars().nth(0) == Some('f')
        {
            let forward_distance = num;
            total_forward_distance += forward_distance;
        }
        else if direction.chars().nth(0) == Some('u')
        {
            let depth = num;
            total_depth -= depth;
        }
        else if direction.chars().nth(0) == Some('d')
        {
            let depth = num;
            total_depth += depth;
        }

    }
    println!("total_forward_distance {}", total_forward_distance);
    println!("total_depth {}", total_depth);
    println!("result: {}", total_forward_distance * total_depth);
}
