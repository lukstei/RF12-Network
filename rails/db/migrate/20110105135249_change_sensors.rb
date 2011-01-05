class ChangeSensors < ActiveRecord::Migration
  def self.up
	remove_column :sensors, :range
	remove_column :sensors, :unit
	add_column :sensors, :station, :string 
	add_column :sensors, :port, :string 
  end

  def self.down	
	add_column :sensors, :unit, :string
	add_column :sensors, :range, :string
	remove_column :sensors, :port
	remove_column :sensors, :station	
  end
end
