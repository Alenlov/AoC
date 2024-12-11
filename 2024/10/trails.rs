use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashSet;
use std::collections::VecDeque;



static DIRS : [(i32,i32); 4] = [(1,0),(-1,0),(0,1),(0,-1)];

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn trail_scores(start : (i32,i32), map : Vec<Vec<u32>>, all_paths : bool) -> i32 {
    let mut visited : HashSet<(i32,i32)> = HashSet::new();
    let mut heads : VecDeque<(i32,i32)> = VecDeque::new();
    let n_row = map.len() as i32;
    let n_col = map[0].len() as i32;
    let mut score : i32 = 0;
    heads.push_back(start);
    while !heads.is_empty() {
        let h = heads.pop_front().unwrap();
        if !visited.contains(&h) {
            if !all_paths {
                visited.insert(h);
            }
            let cur_val : u32 = map[h.0 as usize][h.1 as usize];
            if cur_val == 9 {
                score += 1;
            } else {
                for d in DIRS {
                    let new_r = h.0 + d.0;
                    let new_c = h.1 + d.1;
                    if new_r < 0 || new_r >= n_row || new_c < 0 || new_c >= n_col {
                        continue;
                    } else {
                        let new_val : u32 = map[new_r as usize][new_c as usize];
                        if (cur_val + 1) == new_val {
                            heads.push_back((new_r,new_c));
                        }
                    }
                }
            }
            
        }
        
    }
    return score;
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
    let char_matrix : Vec<Vec<u32>> = lines.into_iter().map(|line| line.chars().filter_map(|c| c.to_digit(10)).collect()).collect();
    let mut trail_heads: HashSet<(i32,i32)> = HashSet::new();
    let n_row : i32 = char_matrix.len() as i32;
    let n_col : i32 = char_matrix[0].len() as i32;
    for r in 0..n_row {
        for c in 0..n_col {
            let type_char : u32 = char_matrix[r as usize][c as usize];
            if type_char == 0 {
                trail_heads.insert((r,c));
            }
        }
    }
    let mut ans_a : i32 = 0;
    let mut ans_b : i32 = 0;
    for h in trail_heads {
        ans_a += trail_scores(h, char_matrix.clone(), false);
        ans_b += trail_scores(h, char_matrix.clone(), true);
    }
    println!("Answer part A: {}", ans_a);
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
