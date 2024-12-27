use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use regex::Regex;
use std::collections::HashSet;

#[derive(Clone)]
struct Robot {
    r : i64,
    c : i64,
    vr : i64,
    vc : i64,
}

impl Robot {
    fn step(&mut self, max_r : i64, max_c : i64) {
        self.r += self.vr;
        self.c += self.vc;
        self.r = ((self.r % max_r) + max_r) % max_r;
        self.c = ((self.c % max_c) + max_c) % max_c; 
    }
}

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn plot_robots(robots : Vec<Robot>, max_r : i64, max_c : i64) {
    let mut points_to_print : HashSet<(i64,i64)> = HashSet::new();
    for robot in robots {
        points_to_print.insert((robot.r,robot.c));
    }
    for r in 0..max_r {
        for c in 0..max_c {
            if points_to_print.contains(&(r,c)) {
                print!("#");
            } else {
                print!(" ");
            }
        }
        println!("");
    }
}

fn calc_vars(robots : Vec<Robot>) -> (i64, i64) {
    let mut sum_r : i64 = 0;
    let mut sum_r2 : i64 = 0;
    let mut sum_c : i64 = 0;
    let mut sum_c2 : i64 = 0;
    let num_robots : i64 = robots.len() as i64;
    
    for robot in robots {
        sum_r += robot.r;
        sum_r2 += robot.r*robot.r;
        sum_c += robot.c;
        sum_c2 += robot.c*robot.c;
    }
    let var_r : i64 = sum_r2/num_robots - (sum_r/num_robots * sum_r/num_robots);
    let var_c : i64 = sum_c2/num_robots - (sum_c/num_robots * sum_c/num_robots);
    return (var_r, var_c)
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        return Ok(());
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    contents = contents.trim().to_string();
    let lines : Vec<&str> = split_lines(&contents);
    let mut robots : Vec<Robot> = Vec::new();

    let mut max_r : i64 = 103;
    let mut max_c : i64 = 101;
    if lines.len() < 20 {
        max_r = 7;
        max_c = 11;
    }

    let re_p = Regex::new(r"p=(\d+),(\d+) v=(\-?\d+),(\-?\d+)").unwrap();

    let mut q1 : i64 = 0;
    let mut q2 : i64 = 0;
    let mut q3 : i64 = 0;
    let mut q4 : i64 = 0;

    for line in lines {
        if re_p.is_match(line) {
            let (_, [str_pc,str_pr,str_vc,str_vr]) = re_p.captures(line).unwrap().extract();
            let pc = str_pc.parse::<i64>().unwrap();
            let pr = str_pr.parse::<i64>().unwrap();
            let vc = str_vc.parse::<i64>().unwrap();
            let vr = str_vr.parse::<i64>().unwrap();
            robots.push(Robot{r: pr, c: pc, vr: vr, vc:vc});
            // After 100 steps
            let c = ((pc + 100*vc) % max_c + max_c) % max_c;
            let r = ((pr + 100*vr) % max_r + max_r) % max_r;
            if (c != max_c/2) && (r != max_r/2) {
                let left : bool = c < max_c/2;
                let up : bool = r < max_r/2;

                if left && up {
                    q1 += 1;
                } else if left && (!up) {
                    q3 += 1;
                } else if (!left) && up {
                    q2 += 1;
                } else if (!left) && (!up) {
                    q4 += 1;
                }
            }

        }
        
    }
    

    let mut off_r : i64 = 0;
    let mut off_c : i64 = 0;
    let (mut min_var_r, mut min_var_c) : (i64, i64) = calc_vars(robots.clone());
    for itr in 1..104 {
        for robot in &mut robots {
            robot.step(max_r, max_c);
        }

        let (var_r, var_c) : (i64, i64) = calc_vars(robots.clone());
        if var_r < min_var_r {
            min_var_r = var_r;
            off_r = itr;
        }
        if var_c < min_var_c {
            min_var_c = var_c;
            off_c = itr;
        }
        
    }

    let mut ans_b : i64 = off_r;
    let mut found : bool = (ans_b % max_c) == off_c;
    while !found {
        ans_b += max_r;
        found = (ans_b % max_c) == off_c;
    }

    let ans_a : i64 = q1 * q2 * q3 * q4;
    println!("Answer part A: {}", ans_a);
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
