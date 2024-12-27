use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashMap;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn matches(key: &[usize;5], lock: &[usize;5]) -> bool {
    for i in 0..5 {
        if key[i] + lock[i] > 5 {
            return false
        }
    }
    return true
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
    let mut keys: Vec<[usize;5]> = Vec::new();
    let mut locks: Vec<[usize;5]> = Vec::new();
    let mut start: usize = 0;
    let mut new_key: bool = true;
    for i in 0..lines.len() {
        if new_key {
            start = i;
            new_key = false;
        }
        if lines[i].len() == 0 || i == lines.len()-1 {
            let mut stop = i;
            if i == lines.len()-1 {stop = lines.len();}
            let mold_matrix: Vec<Vec<char>> = lines[start..stop].into_iter().map(|line| line.chars().collect()).collect();
            let mut mold: [usize;5] = [0; 5];
            if lines[start] == "#####" {
                
                for c in 0..mold_matrix[0].len() {
                    for r in 1..mold_matrix.len() {
                        if mold_matrix[r][c] == '.' {
                            mold[c] = r-1;
                            break
                        }
                    }
                }
                locks.push(mold);
            } else {
                for c in 0..mold_matrix[0].len() {
                    for r in 1..mold_matrix.len() {
                        if mold_matrix[mold_matrix.len() - 1 - r][c] == '.' {
                            mold[c] = r-1;
                            break
                        }
                    }
                }
                keys.push(mold);
            }
            new_key = true;
        }


    }

    let mut ans_a = 0;
    for lock in &locks {
        for key in &keys {
            if matches(key, lock) {
                ans_a += 1;
            }
        }
    }
    

    println!("Answer part A: {}", ans_a);

    Ok(())
}
