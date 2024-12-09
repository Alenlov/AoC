use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

static XMAS : [char; 4] = ['X', 'M', 'A', 'S'];

static MAS : [char; 3] = ['M', 'A', 'S'];

fn get_dir(d : i32) -> (i32,i32) {
    match d {
        0 => (1,0),
        1 => (1,1),
        2 => (0,1),
        3 => (-1,1),
        4 => (-1,0),
        5 => (-1,-1),
        6 => (0,-1),
        7 => (1,-1),
        _ => (0,0),
    }
}

fn found_word(r : usize, c : usize, dir : i32, ind : usize, word_map : &Vec<Vec<char>>) -> i64 {
    if ind == 4 {return 1;}
    let max_row : i32 = word_map.len() as i32;
    let max_col : i32 = word_map[0].len() as i32;
    let new_r = r as i32 + get_dir(dir).0;
    let new_c = c as i32 + get_dir(dir).1;
    if new_r < 0 || new_r >= max_row || new_c < 0 || new_c >= max_col {
        return 0;
    }
    if word_map[new_r as usize][new_c as usize] == XMAS[ind] {
        return found_word(new_r as usize, new_c as usize, dir, ind+1, word_map);
    }
    return 0;
}

fn check_x(r : usize, c : usize, word_map : &Vec<Vec<char>>) -> i64 {
    let max_row : usize = word_map.len();
    let max_col : usize = word_map[0].len();
    if r == 0 || c == 0 || r == max_row-1 || c == max_col-1 {return 0;}
    let mut diag1 : bool = false;
    let mut diag2 : bool = false;
    // Diag 1
    let d11 : char = word_map[r-1][c-1];
    let d12 : char = word_map[r+1][c+1];
    if (d11 == MAS[0] && d12 == MAS[2]) || (d11 == MAS[2] && d12 == MAS[0]) {
        diag1 = true;
    }
    // Diag 2
    let d21 : char = word_map[r+1][c-1];
    let d22 : char = word_map[r-1][c+1];
    if (d21 == MAS[0] && d22 == MAS[2]) || (d21 == MAS[2] && d22 == MAS[0]) {
        diag2 = true;
    }
    if diag1 && diag2 {
        println!("Found with A at {},{}",r,c);
        println!("Diag 1: {} A {}",d11,d12);
        println!("Diag 2: {} A {}",d21,d22);
        return 1;
    } else {
        return 0;
    }
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        return Ok(());
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines : Vec<&str> = split_lines(&contents);
    let char_matrix : Vec<Vec<char>> = lines.into_iter().map(|line| line.chars().collect()).collect();
    
    let num_row : usize = char_matrix.len();
    let num_col : usize = char_matrix[0].len();

    let mut ans_a: i64 = 0;
    let mut ans_b: i64 = 0;

    for r in 0..num_row {
        for c in 0..num_col {
            if char_matrix[r][c] == XMAS[0] {
                for d in 0..8 {
                    ans_a += found_word(r,c,d,1,&char_matrix);
                }
            } else if char_matrix[r][c] == MAS[1] {
                ans_b += check_x(r, c, &char_matrix);
            }
        }
    }

   
    println!("Answer part A: {}", ans_a);
    
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
