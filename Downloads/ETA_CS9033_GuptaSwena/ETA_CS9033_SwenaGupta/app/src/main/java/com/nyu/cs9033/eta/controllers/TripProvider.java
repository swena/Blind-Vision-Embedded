package com.nyu.cs9033.eta.controllers;

/**
 * Created by swenagupta on 4/1/16.
 */
public class TripProvider {
    private String trip_name;
    /*private String trip_loc;
    private String trip_date;
    private String trip_time;
    private String trip_admin;
    private String trip_friends;   */

    public String getTrip_name() {
        return trip_name;
    }

    public void setTrip_name(String trip_name) {
        this.trip_name = trip_name;
    }

    /*public String getTrip_loc() {
        return trip_loc;
    }

    public void setTrip_loc(String trip_loc) {
        this.trip_loc = trip_loc;
    }

    public String getTrip_date() {
        return trip_date;
    }

    public void setTrip_date(String trip_date) {
        this.trip_date = trip_date;
    }

    public String getTrip_time() {
        return trip_time;
    }

    public void setTrip_time(String trip_time) {
        this.trip_time = trip_time;
    }

    public String getTrip_admin() {
        return trip_admin;
    }

    public void setTrip_admin(String trip_admin) {
        this.trip_admin = trip_admin;
    }

    public String getTrip_friends() {
        return trip_friends;
    }

    public void setTrip_friends(String trip_friends) {
        this.trip_friends = trip_friends;
    }
      */
    public TripProvider(String trip_name)
    {
        this.trip_name=trip_name;

        /*this.trip_loc=trip_loc;
        this.trip_time=trip_time;
        this.trip_date=trip_date;
        this.trip_admin=trip_admin;
        this.trip_friends=trip_friends;     */
    }

}
