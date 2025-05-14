log-file compressor & analyzer

this program uses huffman coding to compress an entire log file into a bitstream (written to compressed.txt)
and then scans for "ERROR" lines to report the top 10 most frequent error messages (written to error\_report.txt).

test run:
enter log filename: sample.log
compressed output written to compressed.txt

top error messages:
ERROR connection lost (2 times)
ERROR disk failure (1 times)

analysis complete.
