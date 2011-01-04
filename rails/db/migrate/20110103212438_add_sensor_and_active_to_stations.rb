class AddSensorAndActiveToStations < ActiveRecord::Migration
  def self.up
	add_column :stations, :sensor, :string 
	add_column :stations, :active, :boolean
  end

  def self.down
	remove_column :stations, :sensor
	remove_column :stations, :active
  end
end
