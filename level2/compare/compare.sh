NC='\033[0m' # No Color
GREEN='\033[0;32m'

echo -e "${GREEN}Comparing has started!${NC}"
echo
for file in ../tests/ete/*.dat; do
    printf "%s\n" $file
    ../../build/level2/compare/comp2 < $file
    printf "\n" 
done