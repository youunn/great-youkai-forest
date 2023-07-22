fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut io = cp::io::default();
    let t: usize = io.read()?;
    for _ in 0..t {
        let a = 1usize;
        let b = 2usize;
        io.print(a / cp::cmp::max / b)?;
    }

    Ok(())
}

#[cfg(sdm)]
#[allow(dead_code)]
#[path = "../../lib/cp"]
mod cp {
    pub mod cmp;
    pub mod io;
}
