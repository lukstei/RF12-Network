class RemoveStationFromSensors < ActiveRecord::Migration
  def self.up
	remove_column :sensors, :station
  end

  def self.down
	add_column :sensors, :station, :string 
  end
end
