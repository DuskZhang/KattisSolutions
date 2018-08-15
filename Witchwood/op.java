import java.math.*;
import java.util.*;


public class op {
	
	
	public static void main(String[] args) {

	Scanner sc = new Scanner(System.in);
	final double INF = 1000000000;
	int numLogs, locations, burnTime;
	numLogs = sc.nextInt();
	locations = sc.nextInt();
	burnTime = sc.nextInt();
	int time;
	double prob;
	ArrayList<Location> places = new ArrayList<Location>();;
	while (locations-- > 0) {
		time = sc.nextInt();
		prob = sc.nextDouble();
		double probGotEm = 1 - prob;
		Location pair = new Location(probGotEm, time) ;
		places.add(pair);
	}
	Collections.sort(places, new Comparator<Location>() {
	    //override
	    public int compare(Location c1, Location c2) {
	        return Double.compare(c1.getProb(), c2.getProb());
	    }
	});
	sc.close();
	int index = 0;
	BigDecimal totalTime = new BigDecimal(0);
	
	while (numLogs-- > 0) {
		double nmTrips;
		double nmBurns;
		BigDecimal bestTime = new BigDecimal(INF);
		//bestTime is the best amount of time to get this log
		for (int i = index; i < places.size(); ++i) {
			nmTrips = 1 / places.get(i).getProb();
			nmBurns = nmTrips - 1;
			BigDecimal burnTimeLost = totalTime.add(new BigDecimal(burnTime)).multiply(new BigDecimal (nmBurns));
			BigDecimal tripTimeLost = new BigDecimal(nmTrips * places.get(i).getTime());
			if (bestTime.compareTo(burnTimeLost.add(tripTimeLost)) == 1) {
				
				bestTime = burnTimeLost.add(tripTimeLost);
				index = i;
			}
		}
		totalTime = totalTime.add(bestTime);
	}
	System.out.println( totalTime);

	}
	
	
}
