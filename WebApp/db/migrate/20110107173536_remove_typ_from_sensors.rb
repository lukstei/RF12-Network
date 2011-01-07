class RemoveTypFromSensors < ActiveRecord::Migration
  def self.up
	remove_column :sensors, :typ 
  end

  def self.down
	add_column :sensors, :typ, :string 
  end
end
