// input file path as parameter
use std::fs::File;

pub fn record_iter(file: &str) -> std::io::Result<()> {
    let file = File::open(file)?;
    Ok(())
}